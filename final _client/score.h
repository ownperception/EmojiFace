#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>


class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent = 0);
    void increase(const float b);
    int getScore();
private:
    float score;
};

#endif // SCORE_H
