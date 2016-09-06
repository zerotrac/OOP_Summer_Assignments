#include "qcherryweapon.h"

QCherryWeapon::QCherryWeapon()
{
    atk = 99999999;
    duration = 1;
    bullet = 99999999;
    spdX = 0;
    spdY = 0;
    countPic = 0;
}

QCherryWeapon::~QCherryWeapon()
{

}

bool QCherryWeapon::inRange(QUnit* unit)
{
    double centerX = this->pos().x() + this->width() / 2.0;
    double centerY = this->pos().y() + this->height() / 2.0;
    QPoint point = unit->getCenter();
    if (std::max(std::abs(point.x() - centerX), std::abs(point.y() - centerY)) <= 120) return true;
    return false;
}

void QCherryWeapon::updateInfo()
{
    --duration;
}
