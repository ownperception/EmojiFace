#ifndef TIMER_H
#define TIMER_H
#include <QTimer>
#include <QGraphicsTextItem>

class Timer:public QGraphicsTextItem
{
    Q_OBJECT
public:
    Timer(QGraphicsItem * parent = 0);
    int getTime();
public slots:
    void decrease();
private:
    QTimer * timer;
    int time;
};

#endif // TIMER_H
