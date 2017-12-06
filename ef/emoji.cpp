#include "emoji.h"
#include "game.h"
#include <stdlib.h>
#include <QDebug>

extern Game * game;

Emoji::Emoji(QGraphicsItem * parent, int num)
    :QGraphicsPixmapItem(parent), num(num)
{
    sprintf(filename,":/images/%d.png",num);
    setPixmap(QPixmap(filename));

    etimer = new QTimer(this);
    connect(etimer,SIGNAL(timeout()),this,SLOT(result()));

    etimer->start(200);
}

void Emoji::next_emoji(){
    num = random() % 13 + 1;
    sprintf(filename,":/images/%d.png",num);
    setPixmap(QPixmap(filename));
}

void Emoji::result(){
    int res = random() % 75;
    if (res > 70){
        next_emoji();
        float b = res*0.7;
        game->increasescore(b);
    }
}

void Emoji::settex(){
    setPixmap(QPixmap(filename));
}

void Emoji::stoptimer(){
    if(etimer->isActive())
    {
        etimer->stop();
    }
}
