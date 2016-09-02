#include "qwallnut.h"

QWallnut::QWallnut(int _id)
{
    id = _id;
    hp = baseHp = 4000;
    cd = baseCd = 0;
    rng = baserng = 0;
    bullet = 1;
    shell = 0;
    spdX = spdY = baseSpdX = baseSpdY = 0;
    weapon = nullptr;

    countPic = 3;
    for (int i = 0; i < countPic; ++i)
    {
        QMovie* dummy = new QMovie("Resources/plants/wallnut/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/wallnut/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QWallnut::~QWallnut()
{

}

bool QWallnut::canAttack(QUnit* unit)
{
    return false;
}

std::vector<QWeapon*> QWallnut::attack()
{
    std::vector<QWeapon*> weapons;
    return weapons;
}

bool QWallnut::canGenerateSunshine()
{
    return false;
}

QSunshine* QWallnut::generateSunshine(int _id)
{
    return nullptr;
}

bool QWallnut::isMushroom()
{
    return false;
}

bool QWallnut::canLitUp()
{
    return true;
}

void QWallnut::updateInfo()
{
    if (hp >= 2666)
    {
        currentPic = 0;
    }
    else if (hp >= 1333)
    {
        currentPic = 1;
    }
    else
    {
        currentPic = 2;
    }
    this->setMovie(pics[currentPic]);
}
