#include "game.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <stdlib.h>

Game::Game(QWidget *parent)
    :QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    QPixmap pim(":/images/bckg.jpg");
    scene->setBackgroundBrush(pim.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    emoji = new Emoji();
    emoji->settex();
    emoji->setPos(335,10);
    emoji->setFlag(QGraphicsItem::ItemIsFocusable);
    emoji->setFocus();
    scene->addItem(emoji);

    score = new Score();
    scene->addItem(score);

    face = new Face();
    face->setPos(130,150);
    face->setScale(0.8);
    scene->addItem(face);

    time = new Timer();
    time->setPos(650,0);
    scene->addItem(time);
    show();
}
void Game::stopemotimer()
{
    emoji->stoptimer();
}
void Game::increasescore(const float b)
{
    score->increase(b);
}

