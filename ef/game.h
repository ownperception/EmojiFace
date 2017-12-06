#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "emoji.h"
#include "score.h"
#include "face.h"
#include "timer.h"
#include <QGraphicsItem>
#include <QKeyEvent>

class Game:public QGraphicsView{
public:
    Game(QWidget *parent = nullptr);
    void increasescore(const float b);
    void stopemotimer();
private:
    QGraphicsScene * scene;
    Emoji * emoji;
    Score * score;
    Face  * face;
    Timer * time;

};

#endif // GAME_H
