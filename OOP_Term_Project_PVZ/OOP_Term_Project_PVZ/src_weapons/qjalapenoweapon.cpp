#include "qjalapenoweapon.h"

QJalapenoWeapon::QJalapenoWeapon()
{
    atk = 99999999;
    duration = 1;
    bullet = 99999999;
    spdX = 0;
    spdY = 0;
    countPic = 0;
}

QJalapenoWeapon::~QJalapenoWeapon()
{

}

bool QJalapenoWeapon::inRange(QUnit* unit)
{
    double centerY = this->pos().y() + this->height() / 2.0;
    QPoint point = unit->getCenter();
    if (std::abs(point.y() - centerY) <= 30) return true;
    return false;
}

void QJalapenoWeapon::updateInfo()
{
    --duration;
}
