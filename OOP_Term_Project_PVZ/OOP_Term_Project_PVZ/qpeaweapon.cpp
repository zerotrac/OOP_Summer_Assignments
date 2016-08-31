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
    double centerX = this->pos().x() + this->width() / 2.0;
    double centerY = this->pos().y() + this->height() / 2.0;
    if (centerX >= unit->pos().x() && centerX <= unit->pos().x() + unit->width()
     && centerY >= unit->pos().y() && centerY <= unit->pos().y() + unit->height()) return true;
    return false;
}
