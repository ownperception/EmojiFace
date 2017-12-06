#include "timer.h"
#include "game.h"

extern Game * game;
Timer::Timer(QGraphicsItem * parent)
    : QGraphicsTextItem(parent)
{
    time = 60;
    setPlainText(QString("Time left: ") + QString::number(time));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(decrease()));
    timer->start(1000);
}

void Timer::decrease()
{
    time--;
    setPlainText(QString("Time left: ") + QString::number(time));
    if (time <= 0)
    {
        timer->stop();
        game->stopemotimer();
    }
}
