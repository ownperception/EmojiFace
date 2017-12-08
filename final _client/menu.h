#ifndef MENU_H
#define MENU_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

class Menu: public QGraphicsTextItem
{
public:
    Menu(QGraphicsItem * parent = nullptr, bool start = false);
private:
    bool start;
    QTimer * timer;
    QGraphicsTextItem * start;
};

#endif // MENU_H
