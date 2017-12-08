#include <QApplication>
#include "game.h"
#include <cv.h>
#include <highgui.h>
#include <QGraphicsPixmapItem>
#include <qtipl.h>
#include  "mainwindow.h"

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w(argc,argv);
    w.show();

    return a.exec();
}
