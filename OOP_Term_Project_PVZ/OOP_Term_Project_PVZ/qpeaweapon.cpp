#include "qpeaweapon.h"

QPeaWeapon::QPeaWeapon(int _currentPic)
{
    duration = 99999999;
    bullet = 1;
    spdX = 8;
    spdY = 0;
    countPic = 3;
    for (int i = 0; i < countPic; ++i)
    {
        QPixmap dummy("Resources/weapons/pea/" + QString::number(i) + ".gif");
        pics.push_back(dummy);
    }
    currentPic = _currentPic;
    this->setFixedSize(pics[0].size());
    this->setPixmap(pics[currentPic]);
}

QPeaWeapon::~QPeaWeapon()
{

}

bool QPeaWeapon::inRange(QUnit *unit)
{
    return true;
}
