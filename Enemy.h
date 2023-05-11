#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <vector>
#include <QPointF>
using namespace std;

class Enemy: public QObject, public QGraphicsRectItem{
    Q_OBJECT

public:
    //Constructores
    Enemy(int stepSize, QGraphicsItem* parent=nullptr);

    //Setters
    void setPoints(const vector<QPointF>& points);

public slots:
    void move();

private:
    vector<QPointF> points_;
    size_t targetPoint_;
    int stepSize_;

    bool targetReached();
    bool atLastPoint();
    void setNextTarget();
    void moveTowardsTarget();
};

#endif // ENEMY_H
