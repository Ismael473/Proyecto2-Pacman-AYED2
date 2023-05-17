#include "Enemy.h"
#include <QLineF>
#include <QTimer>
#include <QDebug>
#include <QBrush>
#include <cassert>

using namespace std;

/*!
 * \brief Enemy::Enemy crea la clase enemigo
 * \param stepSize que tanto avanza el enemigo con cada paso que da
 * \param parent
 */
Enemy::Enemy( int stepSize, QGraphicsItem *parent):
    QGraphicsRectItem(parent),
    targetPoint_(0),
    stepSize_(stepSize),
    points_()
{
    //Mueve a los enemigos
    QTimer* moveTimer = new QTimer(this);
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    moveTimer->start(500);

    //Dibuja a los enemigos
    setRect(0,0,stepSize,stepSize);
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);

}

/*!
 * \brief Enemy::move mueve al enemigo
 * \param no recibe parametros
 * \return no retorna nada
 */
void Enemy::move(){

    if (atLastPoint()){
        return;
    }


    moveTowardsTarget();


    if (targetReached()){
        setNextTarget();
    }
}

/*!
 * \brief Enemy::setPoints
 * \param points
 * \return no retorna nada
 */
void Enemy::setPoints(const vector<QPointF> &points){

    points_ = points;


    targetPoint_ = 1;
}

/*!
 * \brief Enemy::targetReached
 * \param no recibe parametros
 * \return retorna true si el enemigo a alcanzado su objetivo
 */
bool Enemy::targetReached(){
    const int EPSILON = 50;


    QPointF target = points_[targetPoint_];
    QLineF line(pos(),target);

    return (line.length() < EPSILON);
}

/*!
 * \brief Enemy::atLastPoint
 * \param no recibe parametros
 * \return retorna true si el enemigo se encuentra en el punto final
 */
bool Enemy::atLastPoint(){

    int veclength = points_.size();
    int targetPt = targetPoint_;
    bool cond = targetPt >= veclength;
    return (cond);
}

/*!
 * \brief Enemy::setNextTarget
 * \param no recibe parametrps
 * \return no retorna nada
 */
void Enemy::setNextTarget(){

    ++targetPoint_;
}

/*!
 * \brief Enemy::moveTowardsTarget
 * \param no tiene parametros
 * \return no retorna nada
 */
void Enemy::moveTowardsTarget(){


    QPointF target = points_[targetPoint_];
    QLineF line(pos(),target);
    line.setLength(stepSize_);
    moveBy(line.dx(),line.dy());
}
