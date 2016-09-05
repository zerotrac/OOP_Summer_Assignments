#include "qzombie.h"

QZombie::QZombie()
{
    freezeDebuff = 0;
    stunDebuff = 0;
    rageBuff = 0;

    spdY = 0.0;
    baseSpdY = 0.0;
}

QZombie::~QZombie()
{

}

bool QZombie::isPlant()
{
    return false;
}

bool QZombie::isZombie()
{
    return true;
}

void QZombie::setAxis(double dx, double dy)
{
    posX = dx;
    posY = dy - this->height();
    this->setGeometry(dx, dy - this->height(), 0, 0);
}

