#include "Health.h"
#include <QFont>


Health::Health(QGraphicsItem *parent)
{

    health_ = 0;

    setPlainText(QString("Score: ") + QString::number(health_));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void Health::decrease(){
    health_++;
    setPlainText(QString("Score: ") + QString::number(health_));

}

int Health::getHealth(){
    return health_;
}
