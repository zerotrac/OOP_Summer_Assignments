#include "qplant.h"

QPlant::QPlant()
{
    spdX = 0.0;
    spdY = 0.0;
    baseSpdX = 0.0;
    baseSpdY = 0.0;
}

QPlant::~QPlant()
{

}

bool QPlant::isPlant()
{
    return true;
}

bool QPlant::isZombie()
{
    return false;
}

QPoint QPlant::getCenter() const
{
    return QPoint(this->pos().x() + this->width() / 2, this->pos().y() + this->height() / 2);
}
