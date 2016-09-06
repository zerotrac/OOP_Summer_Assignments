#include "qpeaweapon.h"

QPeaWeapon::QPeaWeapon(int _currentPic)
{
    atk = 20;
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

bool QPeaWeapon::inRange(QUnit* unit)
{   
    double centerX = this->pos().x() + this->width() / 2.0;
    double centerY = this->pos().y() + this->height() / 2.0;
    QPoint point = unit->getCenter();
    if (std::abs(point.x() - centerX) <= 15 && std::abs(point.y() - centerY) <= 30) return true;
    return false;
}

void QPeaWeapon::updateInfo()
{
    this->setGeometry(this->pos().x() + spdX, this->pos().y() + spdY, 0, 0);
    if (currentPic == 2) atk = 40; else atk = 20;
}

QBuff QPeaWeapon::getBuff() const
{
    if (currentPic == 0)
    {
        return QBuff(10 * 1000 / TIME_ELAPSE, 0);
    }
    else
    {
        return QBuff(0, 0);
    }
}
