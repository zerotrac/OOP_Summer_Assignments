#include "qhandweapon.h"

QHandWeapon::QHandWeapon(int _atk)
{
    atk = _atk;
    duration = 1;
    bullet = 1;
    spdX = 0;
    spdY = 0;
    countPic = 0;
}

QHandWeapon::~QHandWeapon()
{

}

bool QHandWeapon::inRange(QUnit *unit)
{
    double centerX = this->pos().x() + this->width() / 2.0;
    double centerY = this->pos().y() + this->height() / 2.0;
    QPoint point = unit->getCenter();
    if (std::abs(point.x() - centerX) <= 40 && std::abs(point.y() - centerY) <= 60) return true;
    return false;
}

void QHandWeapon::updateInfo()
{
    --duration;
}
