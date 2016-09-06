#include "qglobalweapon.h"

QGlobalWeapon::QGlobalWeapon()
{
    atk = 20;
    duration = 1;
    bullet = 99999999;
    spdX = 0;
    spdY = 0;
    countPic = 0;
}

QGlobalWeapon::~QGlobalWeapon()
{

}

bool QGlobalWeapon::inRange(QUnit* unit)
{
    return true;
}

void QGlobalWeapon::updateInfo()
{
    --duration;
}

QBuff QGlobalWeapon::getBuff() const
{
    return QBuff(20 * 1000 / TIME_ELAPSE, 4 * 1000 / TIME_ELAPSE);
    //return QBuff(20 * 1000 / TIME_ELAPSE, 0);
}
