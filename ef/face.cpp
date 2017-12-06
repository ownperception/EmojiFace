#include "face.h"
#include "game.h"
#include "qtipl.h"
#include <QDebug>
#include <QTimer>

using namespace cv;
extern Game * game;
Face::Face(QGraphicsItem * parent)
    :QGraphicsPixmapItem(parent)
{
        capWebcam.open(0);

        if(!capWebcam.isOpened())
        {
            qDebug("nocamera");
            return;
        }

        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGUI()));
        timer->start(20);
}
void Face::processFrameAndUpdateGUI()
{
    capWebcam.read(matFrame);
    if(matFrame.empty()) return;

    QImage qimgFrame((uchar*)matFrame.data, matFrame.cols, matFrame.rows, matFrame.step, QImage::Format_RGB888);
    this->setPixmap(QPixmap::fromImage(qimgFrame));
}
