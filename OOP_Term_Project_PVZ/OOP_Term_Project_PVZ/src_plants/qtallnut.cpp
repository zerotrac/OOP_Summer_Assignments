#include "qtallnut.h"

QTallnut::QTallnut(int _id)
{
    id = _id;
    hp = baseHp = 8000;
    cd = baseCd = 0;
    rng = baserng = 0;
    bullet = 1;
    shell = 0;
    spdX = spdY = baseSpdX = baseSpdY = 0;
    weapon = nullptr;

    countPic = 3;
    for (int i = 0; i < countPic; ++i)
    {
        QMovie* dummy = new QMovie("Resources/plants/tallnut/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/tallnut/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QTallnut::~QTallnut()
{

}

bool QTallnut::canAttack(QUnit* unit)
{
    return false;
}

std::vector<QWeapon*> QTallnut::attack()
{
    std::vector<QWeapon*> weapons;
    return weapons;
}

bool QTallnut::canGenerateSunshine()
{
    return false;
}

QSunshine* QTallnut::generateSunshine(int _id)
{
    return nullptr;
}

bool QTallnut::isMushroom()
{
    return false;
}

bool QTallnut::canLitUp()
{
    return false;
}

void QTallnut::updateInfo()
{
    if (hp >= 5333)
    {
        currentPic = 0;
    }
    else if (hp >= 2666)
    {
        currentPic = 1;
    }
    else
    {
        currentPic = 2;
    }
    this->setMovie(pics[currentPic]);
}
