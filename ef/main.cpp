#include <QApplication>
#include "game.h"
#include <cv.h>
#include <highgui.h>
#include <QGraphicsPixmapItem>
#include <qtipl.h>

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();

    return a.exec();
}
