#ifndef EMOJI_H
#define EMOJI_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

class Emoji: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Emoji(QGraphicsItem * parent = 0, int num = 1);
    void next_emoji();
    void settex();
    void stoptimer();
public slots:
    void result();
private:
    int num;
    char filename[20];
    QTimer * etimer;
};

#endif // EMOJI_H
