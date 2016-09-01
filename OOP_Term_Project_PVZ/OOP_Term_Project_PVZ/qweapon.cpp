#include "qweapon.h"
#include <iostream>

QWeapon::QWeapon()
{

}

QWeapon::~QWeapon()
{

}

bool QWeapon::outofDuration()
{
    double centerX = this->pos().x() + this->width() / 2.0;
    double centerY = this->pos().y() + this->height() / 2.0;
    return (duration <= 0 || bullet <= 0 || centerX < 0 || centerX > WINDOW_WIDTH || centerY < 0 || centerY > WINDOW_HEIGHT);
}

void QWeapon::setAxis(double dx, double dy)
{
    this->setGeometry(dx, dy - this->height(), 0, 0);
}

void QWeapon::setLit(int _litID)
{
    if (litID != _litID && currentPic < countPic - 1)
    {
        litID = _litID;
        ++currentPic;
        this->setPixmap(pics[currentPic]);
    }
}

void QWeapon::decBullet()
{
    --bullet;
}
