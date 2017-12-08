#include "emoji.h"
#include "game.h"
#include <stdlib.h>
#include <emojiClass.h>
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
    num = random() % 5 + 1;
    sprintf(filename,":/images/%d.png",num);
    setPixmap(QPixmap(filename));
}

void Emoji::result(){
    emoji_struct res = detect_emotion(game->getMatFrame());
    if(!res.is_error){
        switch (num) {
        case 1:
            if(res.no > 50)
            {
                game->increasescore(res.no);
                next_emoji();
            }
            break;
        case 2:
            if (res.happy > 50)
            {
                game->increasescore(res.happy);
                next_emoji();
            }
            break;
        case 3:
            if (res.sad > 50)
            {
                game->increasescore(res.sad);
                next_emoji();
            }
            break;
        case 4:
            if (res.angry > 50)
            {
                game->increasescore(res.angry);
                next_emoji();
            }
            break;
        case 5:
            if (res.surprised > 50)
            {
                game->increasescore(res.surprised);
                next_emoji();
            }
        default:
            break;
        }
    } else{
        cout << "ERROR: somthing wrong" << endl;
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
