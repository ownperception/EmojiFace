#ifndef FACE_H
#define FACE_H
#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Face: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public slots:
    void processFrameAndUpdateGUI();
public:
    Face(QGraphicsItem * parent = 0);
private:
    cv::VideoCapture capWebcam;

    cv::Mat matFrame;

    QImage qimgFrame;

    QTimer* timer;
};

#endif // FACE_H
