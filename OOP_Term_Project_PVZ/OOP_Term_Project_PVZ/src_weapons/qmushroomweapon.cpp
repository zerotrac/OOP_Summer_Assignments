#include "qmushroomweapon.h"

QMushroomWeapon::QMushroomWeapon()
{
    atk = 20;
    duration = 99999999;
    bullet = 1;
    spdX = 8;
    spdY = 0;
    countPic = 1;
    for (int i = 0; i < countPic; ++i)
    {
        QPixmap dummy("Resources/weapons/mushroom/" + QString::number(i) + ".gif");
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(pics[0].size());
    this->setPixmap(pics[currentPic]);
}

QMushroomWeapon::~QMushroomWeapon()
{

}

bool QMushroomWeapon::inRange(QUnit* unit)
{
    double centerX = this->pos().x() + this->width() / 2.0;
    double centerY = this->pos().y() + this->height() / 2.0;
    QPoint point = unit->getCenter();
    if (std::abs(point.x() - centerX) <= 15 && std::abs(point.y() - centerY) <= 40) return true;
    return false;
}

void QMushroomWeapon::updateInfo()
{
    this->setGeometry(this->pos().x() + spdX, this->pos().y() + spdY, 0, 0);
}
