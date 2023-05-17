#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{
public:

    Health(QGraphicsItem * parent=0);
    void decrease();
    int getHealth();
    int health_;
private:

    //int health_;

};

#endif // HEALTH_H
