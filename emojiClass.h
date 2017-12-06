#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>

#include "./DATA/NN/NeuralNetworkTrainer.h"
#include "./DATA/NN/TrainingDataReader.h"

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <string>
#include <cmath>
using namespace cv;
using namespace dlib;
using namespace std;

class emojiClass
{
  public:
    emojiClass() {}
    int Init(string face_cascade_name = "../DATA/haarcascade_frontalface_alt.xml", string shape_predictor_name = "../DATA/shape_predictor_68_face_landmarks.dat")
    {
        // Load the cascades
        deserialize(shape_predictor_name) >> this->sp;

        if (!face_cascade.load(face_cascade_name))
        {
            return -1;
        };

        return 0;
    };

    BPN::Network InitNetwork(uint32_t const numInputs,
                             uint32_t const numHidden,
                             uint32_t const numOutputs)
    {
        try
        {

            // Create neural network
            BPN::Network::Settings networkSettings{numInputs, numHidden, numOutputs};

            std::vector<double> weights;
            if (!LoadWeights(weights))
            {
                BPN::Network nn(networkSettings, weights);
                return nn;
            }
            else
            {
                BPN::Network nn(networkSettings);
                return nn;
            }
        }
        catch (exception &e)
        {
            cout << e.what() << endl;
        }
    }

    BPN::NetworkTrainer InitNetworkTrainer(BPN::Network &nn, uint32_t const numInputs,
                                           uint32_t const numHidden,
                                           uint32_t const numOutputs, int maxEpochs = 200, double learningRate = 0.01, double momentum = 0.9)
    {
        try
        {
            // Create neural network trainer
            BPN::NetworkTrainer::Settings trainerSettings;
            trainerSettings.m_learningRate = learningRate;
            trainerSettings.m_momentum = momentum;
            trainerSettings.m_useBatchLearning = true;
            trainerSettings.m_maxEpochs = maxEpochs;
            trainerSettings.m_desiredAccuracy = 98;

            BPN::NetworkTrainer trainer(trainerSettings, &nn);
            return trainer;
        }
        catch (exception &e)
        {
            cout << e.what() << endl;
        }
    }

    int TrainNetwork(BPN::NetworkTrainer &trainer, BPN::Network &nn, std::string trainingDataPath,
                     uint32_t const numInputs,
                     uint32_t const numOutputs)
    {
        try
        {
            BPN::TrainingDataReader dataReader(trainingDataPath, numInputs, numOutputs);
            if (!dataReader.ReadData())
            {
                return 1;
            }

            trainer.Train(dataReader.GetTrainingData());
        }
        catch (exception &e)
        {
            cout << e.what() << endl;
        }
        return 0;
    }

    int SaveWeights(BPN::Network &nn)
    {
        std::vector<double> IHweights = nn.GetInputHiddenWeights();
        std::vector<double> HOweights = nn.GetHiddenOutputWeights();
        std::vector<double> weights;
        for (int i = 0; i < IHweights.size(); i++)
            weights.push_back(IHweights[i]);
        for (int i = 0; i < HOweights.size(); i++)
            weights.push_back(HOweights[i]);
        if (write_d("../DATA/weights.csv", weights))
            return -1;
        return 0;
    }

    int LoadWeights(std::vector<double> &v)
    { /*
        std::vector<double> IHweights = nn.GetInputHiddenWeights();
        std::vector<double> HOweights = nn.GetHiddenOutputWeights();
        std::vector<double> weights;
        for (int i = 0; i < IHweights.size(); i++)
            weights.push_back(IHweights[i]);
        for (int i = 0; i < HOweights.size(); i++)
            weights.push_back(HOweights[i]);
        if (write_d("weights.csv", weights))
            return -1;
        return 1;*/
        return -1;
    }

    std::vector<double> Evaluate(BPN::Network &nn, std::vector<double> vec)
    {
        return nn.Evaluate(vec);
    }

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
    /*
//old
    int write_training_set(std::vector<double> vshape, string path, int type)
    {
        for (int i = 0; i < 5; i++)
        {
            if (i == type)
                vshape.push_back(1);
            else
                vshape.push_back(0);
        }
        if (write_d(path, vshape))
            return -1;
        return 0;
    }
    */
    int write_training_set(std::vector<double> vshape, string path, int type)
    {
        vshape.push_back(type);
        if (write_d(path, vshape))
            return -1;
        return 0;
    }
    
    int detect_emotion(BPN::Network &nn, Mat cv_frame)
    {
        cout << "-- detecting faces..." << endl;
        std::vector<Rect> cv_faces = detectFaces(cv_frame);
        Mat small_frame = cv_frame(cv_faces[0]);
        cv::resize(small_frame, small_frame, cv::Size(80, 80));

        full_object_detection shape = detectShape(small_frame);

        std::vector<Point2d> vshape = shape_toVec(shape);
        //if (normalize(vshape, small_frame.cols, small_frame.rows) == -1)
        //   throw "zero division";

        std::vector<double> vec = important_value(vshape);

        return 0;//evaluate_emotion(nn, vec);
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

    /*
    typedef struct emojy_struct
    {
        double happy;
        double sad;
        double noem;
        int if_error;
    };

    emojy_struct get_emotion()
    {
        return emotion;
    }*/
    /*
    std::vector<Point2d> read_shape(string path)
    {
        streampos begin, end;
        std::ifstream in_file(path, std::ofstream::in);

        //check is opened
        if (!in_file.is_open())
            throw - 1;

        //calc sizeof file
        begin = in_file.tellg();
        in_file.seekg(0, ios::end);
        end = in_file.tellg();
        int size = (end - begin) / sizeof(double);

        //set begining
        in_file.seekg(0, ios::beg);

        std::vector<Point2d> vshape;
        for (int i = 0; i < size / 2; i++)
        {
            double x, y;
            string del;
            in_file >> setw(sizeof(double)) >> x;
            in_file >> setw(sizeof(",")) >> del;
            in_file >> setw(sizeof(double)) >> y;
            if (i != (size / 2) - 1)
                in_file >> setw(sizeof(",")) >> del;
            vshape.push_back(Point2d(x, y));
        }

        in_file.close();
        cout << "file: " << path << " loaded" << endl;
        cout << "size_file " << size << endl;
        cout << "NumPoints " << size / 2 << endl;
        return vshape;
    }*/

    /*
    int write_training_shape(std::vector<Point2d> vshape, string path,int type)
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
        out_file<<type;
        out_file<<"/n";

        out_file.close();
        return 0;
    }*/

  private:
    //emojy_struct emotion;
    shape_predictor sp;
    CascadeClassifier face_cascade;
    // BPN::Network nn;
/*
    int evaluate_emotion(BPN::Network &nn, std::vector<double> vec)
    {
        try
        {
            std::vector<double> res = Evaluate(nn, vec);
            for (int i = 0; i < res.size(); i++)
                cout << i << ": " << res[i] << endl;
        }
        catch (exception &e)
        {
            cout << e.what() << endl;
        }
        catch (...)
        {
            return -1;
        }
        return 0;
    }
*/
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

    int normalize(std::vector<Point2d> &sv, int width, int height)
    {
        if (width != 0 && height != 0)
        {
            for (int i = 0; i < sv.size(); i++)
            {
                sv[i].x /= width;
                sv[i].y /= height;
            }
            return 0;
        }
        return -1;
    }

    /*
    double cmp_vec(std::vector<Point2d> v1, std::vector<Point2d> v2)
    {
        if (v1.size() != v2.size() || v1.size() < 17)
            throw "vec size";

        double rb = 0;
        for (int i = 17; i < 22; i++)
        {
            rb += distance(v1[i], v2[i]);
        }
        ///////////////
        cout << "right eyebrow dist: " << rb << endl;
        //////////////////

        double leb = 0;
        for (int i = 22; i < 27; i++)
        {
            leb += distance(v1[i], v2[i]);
        }
        ///////////////
        cout << "left eyebrow dist: " << leb << endl;
        //////////////////

        double reye = 0;
        for (int i = 36; i < 42; i++)
        {
            reye += distance(v1[i], v2[i]);
        }
        ///////////////
        cout << "right eye dist: " << reye << endl;
        //////////////////

        double leye = 0;
        for (int i = 42; i < 48; i++)
        {
            leye += distance(v1[i], v2[i]);
        }
        ///////////////
        cout << "left eye dist: " << leye << endl;
        //////////////////

        double om = 0;
        for (int i = 48; i < 61; i++)
        {
            om += distance(v1[i], v2[i]);
        }
        ///////////////
        cout << "outmouth dist: " << om << endl;
        //////////////////

        double im = 0;
        for (int i = 61; i < 68; i++)
        {
            im += distance(v1[i], v2[i]);
        }
        ///////////////
        cout << "innermouth dist: " << im << endl;
        //////////////////

        return (rb + leb + reye + leye + om + im);
    }*/
};