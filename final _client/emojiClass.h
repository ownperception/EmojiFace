#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <string>
#include <cmath>
#include <exception>
#include <python3.5/Python.h>
#include <typeinfo>
#include "numpy/arrayobject.h"
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

using namespace cv;
using namespace dlib;
using namespace std;

class emojiClass
{
  public:
    typedef struct emoji_struct
    {
        double no;
        double happy;
        double sad;
        double angry;
        double surprised;
        bool is_error;
    };

    emojiClass() {}
    ~emojiClass() { Py_Finalize(); }
    int Init(string face_cascade_name = "../DATA/haarcascade_frontalface_alt.xml", string shape_predictor_name = "../DATA/shape_predictor_68_face_landmarks.dat")
    {
        // Load the cascades
        deserialize(shape_predictor_name) >> this->sp;

        if (!face_cascade.load(face_cascade_name))
        {
            return -1;
        };

        Py_Initialize();
        _import_array();
        PyImport_ImportModule("sklearn");
        PyRun_SimpleString("from sklearn import svm");
        PyRun_SimpleString("from sklearn.externals import joblib");
        PyRun_SimpleString("import numpy as np");

        return 0;
    };

    std::vector<double> get_training_set(Mat frame)
    {
        std::vector<Rect> cv_faces = detectFaces(frame);

        Mat small_frame = frame(cv_faces[0]);
        cv::resize(small_frame, small_frame, cv::Size(100, 100));

        full_object_detection shape = detectShape(small_frame);

        std::vector<Point2d> vshape = shape_toVec(shape);
        //if (normalize(vshape, small_frame.cols, small_frame.rows) == -1)
        //   throw "zero division";
        std::vector<double> vec = important_value(vshape);

        return vec;
    }
    void show_training_set(Mat frame)
    {
        std::vector<Rect> cv_faces = detectFaces(frame);

        Mat small_frame = frame(cv_faces[0]);
        cv::resize(small_frame, small_frame, cv::Size(100, 100));

        full_object_detection shape = detectShape(small_frame);
        // convert CV to dlib img
        cv_image<bgr_pixel> dl_face(small_frame);
        image_window win1;
        win1.clear_overlay();
        win1.set_image(dl_face);
        win1.add_overlay(render_face_detections(shape));
        cvWaitKey(1000);
    }

    int write_training_set(std::vector<double> vshape, string path, int type)
    {
        vshape.push_back(type);
        if (write_d(path, vshape))
            return -1;
        return 0;
    }

    typename emojiClass::emoji_struct detect_emotion(Mat cv_frame)
    {
        cout << "-- detecting faces..." << endl;
        std::vector<Rect> cv_faces = detectFaces(cv_frame);
        Mat small_frame = cv_frame(cv_faces[0]);
        cv::resize(small_frame, small_frame, cv::Size(80, 80));

        full_object_detection shape = detectShape(small_frame);

        std::vector<Point2d> vshape = shape_toVec(shape);

        std::vector<double> vec = important_value(vshape);

        evaluate_emotion(vec);

        return emotion;
    }

    std::vector<Rect> detectFaces(Mat frame)
    {
        std::vector<Rect> faces;
        Mat frame_gray;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        equalizeHist(frame_gray, frame_gray);
        // Detect faces
        face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
        return faces;
    }

    full_object_detection detectShape(const Mat &cv_frame)
    {
        // convert CV to dlib img
        cv_image<bgr_pixel> dl_face(cv_frame);

        dlib::rectangle rect(point(0, 0), point(cv_frame.cols, cv_frame.rows));
        // Detect shapes
        full_object_detection shape = sp(dl_face, rect);

        return shape;
    }

    emoji_struct get_emotion()
    {
        return emotion;
    }

    int write_training_shape(std::vector<Point2d> vshape, string path, int type)
    {
        std::ofstream out_file(path, std::ios::app | std::ofstream::out);
        if (!out_file.is_open())
            return -1;

        for (int i = 17; i < 27; i++)
        {
            out_file << setw(sizeof(double)) << vshape[i].x;
            out_file << ",";
            out_file << setw(sizeof(double)) << vshape[i].y;
            out_file << ",";
        }
        for (int i = 37; i < vshape.size(); i++)
        {
            out_file << setw(sizeof(double)) << vshape[i].x;
            out_file << ",";
            out_file << setw(sizeof(double)) << vshape[i].y;
            out_file << ",";
        }
        out_file << type;
        out_file << "/n";

        out_file.close();
        return 0;
    }

  private:
    emojiClass::emoji_struct emotion;
    shape_predictor sp;
    CascadeClassifier face_cascade;

    int evaluate_emotion(std::vector<double> vec)
    {
        std::vector<double> res = Evaluate(vec);
        if (res.size() != 6)
            return -1;
        else if (emotion.is_error = res[5])
            return -1;
        emotion.no = res[0];
        emotion.happy = res[1];
        emotion.sad = res[2];
        emotion.angry = res[3];
        emotion.surprised = res[4];
        emotion.is_error = res[5];

        return 0;
    }

    std::vector<double> Evaluate(std::vector<double> vec)
    {
        double *arr = &vec[0];

        string file_path("pypredictor");
        string func_name("predict");

        npy_intp dims = vec.size();
        void *v = reinterpret_cast<void *>(arr);
        try
        {
            if (!v)
                throw 0;

            // _import_array();
            PyObject *pArray = PyArray_SimpleNewFromData(1, &dims, NPY_DOUBLE, arr);
            if (!pArray)
                throw 1;

            wchar_t WBuf[7];
            mbstowcs(WBuf, "../DATA", 7);

            PySys_SetPath(WBuf);

            PyObject *pModule = PyImport_ImportModule(file_path.c_str());
            if (pModule)
            {
                PyObject *pFunc = PyObject_GetAttrString(pModule, func_name.c_str());
                if (pFunc && PyCallable_Check(pFunc))
                {
                    PyObject *pReturn = PyObject_CallFunctionObjArgs(pFunc, pArray, NULL);
                    if (!pReturn || !PyArray_Check(pReturn))
                    {
                        Py_DECREF(pArray);
                        Py_DECREF(pModule);
                        Py_XDECREF(pFunc);
                        throw 4;
                    }

                    PyArrayObject *np_ret = reinterpret_cast<PyArrayObject *>(pReturn);
                    if (!np_ret || PyArray_NDIM(np_ret) != 1)
                    {
                        Py_DECREF(pArray);
                        Py_DECREF(pModule);
                        Py_XDECREF(pFunc);
                        Py_DECREF(pReturn);
                        throw 0;
                    }

                    int len = PyArray_SHAPE(np_ret)[0];
                    double *res = reinterpret_cast<double *>(PyArray_DATA(np_ret));

                    std::vector<double> vres;
                    for (int i = 0; i < len; i++)
                    {
                        vres.push_back(res[i]);
                    }
                    vres.push_back(0);
                    return vres;
                }
                else
                {
                    Py_DECREF(pArray);
                    Py_DECREF(pModule);
                    throw 3;
                }
            }
            else
            {
                Py_DECREF(pArray);
                throw 2;
            }
        }
        catch (int c)
        {
            switch (c)
            {
            case 0:
                cout << "--error cast" << endl;
                break;
            case 1:
                cout << "--error array conv" << endl;
                break;
            case 2:
                PyErr_Print();
                std::cout << "Failed to load " << file_path << endl
                          << std::strerror(errno) << endl;
                break;
            case 3:
                cout << "--error func in pyfile 'predict.py'!" << endl;
                break;
            case 4:
                cout << "--error return array" << endl;
                break;
            case 5:

                break;
            }
        }
        return std::vector<double>{0, 0, 0, 0, 0, 1};
    }

    std::vector<double> important_value(std::vector<Point2d> vshape)
    {
        //significant vertex
        std::vector<Point2d> imp_v;
        for (int i = 17; i < vshape.size(); i++)
        {
            imp_v.push_back(vshape[i]);
        }
        //the centre point
        Point2d c = c_figure(imp_v);

        std::vector<double> res_vec; //resulting vector

        double angle_deviation = atan((vshape[27].y - c.y) / (vshape[27].x - c.x)) * 180 / pi; //deviation angle nose to vertical

        for (int i = 0; i < imp_v.size(); i++)
        {
            res_vec.push_back(imp_v[i].x);                                                                 //Add x
            res_vec.push_back(imp_v[i].y);                                                                 //Add y
            res_vec.push_back(emojiClass::distance(imp_v[i], c));                                          //Add relative distance to center
            res_vec.push_back(atan((imp_v[i].y - c.y) / (imp_v[i].x - c.x)) * 180 / pi - angle_deviation); //Add angle to vertical include angle deviation
        }

        return res_vec;
    }

    int write_d(string path, std::vector<double> vec)
    {
        std::ofstream out_file;
        cout << "writing to '" << path << "' ..." << endl;
        out_file.open(path, std::ios::app);
        if (!out_file.is_open())
        {
            out_file.open(path, std::ios::out);
            if (!out_file.is_open())
                return -1;
        }

        for (int i = 0; i < vec.size(); i++)
        {
            if (i == vec.size() - 1)
                out_file << setw(sizeof(double)) << vec[i];
            else
                out_file << setw(sizeof(double)) << vec[i] << ",";
        }
        out_file << "\n";

        out_file.close();
        cout << "done writing." << endl;
        return 0;
    }

    Point2d c_figure(std::vector<Point2d> v)
    {
        double xc = 0, yc = 0;
        for (int i = 0; i < v.size(); i++)
        {
            xc += v[i].x;
            yc += v[i].y;
        }
        return v.size() != 0 ? Point2d(xc / v.size(), yc / v.size()) : throw - 2;
    }

    double distance(Point2d p1, Point2d p2)
    {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        double res = sqrt(dx * dx + dy * dy);
        return res;
    }

    double abs(double x1)
    {
        return std::sqrt(x1 * x1);
    }

    std::vector<Point2d> shape_toVec(full_object_detection shape)
    {
        std::vector<Point2d> vshape;
        for (int i = 0; i < shape.num_parts(); i++)
        {
            vshape.push_back(Point2d(shape.part(i).x(), shape.part(i).y()));
        }
        return vshape;
    }
};
