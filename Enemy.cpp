#include "Enemy.h"
#include <QLineF>
#include <QTimer>
#include <QDebug>
#include <QBrush>
#include <cassert>


Enemy::Enemy( int stepSize, QGraphicsItem *parent):
    QGraphicsRectItem(parent),
    targetPoint_(0),
    stepSize_(stepSize),
    points_()
{

    QTimer* enemyTimer = new QTimer(this);
    connect(enemyTimer,SIGNAL(timeout()),this,SLOT(move()));
    enemyTimer->start(5000);

    setRect(0,0,stepSize,stepSize);
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);

}

void Enemy::move(){

    if (atLastPoint()){
        return;
    }

    moveTowardsTarget();

    if (targetReached()){
        setNextTarget();
    }
}

void Enemy::setPoints(const std::vector<QPointF> &points){

    points_ = points;
    targetPoint_ = 1;

}

bool Enemy::targetReached(){
    const int EPSILON = 50;

    QPointF target = points_[targetPoint_];
    QLineF line(pos(),target);

    return (line.length() < EPSILON);
}


bool Enemy::atLastPoint(){

    int veclength = points_.size();
    int targetPt = targetPoint_;
    bool cond = targetPt >= veclength;
    return (cond);
}


void Enemy::setNextTarget(){
    ++targetPoint_;
}

void Enemy::moveTowardsTarget(){

    QPointF target = points_[targetPoint_];
    QLineF line(pos(), target);
    line.setLength(stepSize_);
    moveBy(line.dx(), line.dy());

}
