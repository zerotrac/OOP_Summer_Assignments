#include "qsunflower.h"

QSunflower::QSunflower(int _id)
{
    id = _id;
    hp = baseHp = 300;
    cd = 6 * 1000 / TIME_ELAPSE;
    baseCd = 24 * 1000 / TIME_ELAPSE;
    rng = baserng = 0;
    bullet = 1;
    shell = 0;
    spdX = spdY = baseSpdX = baseSpdY = 0;
    weapon = nullptr;
    clicked = true;

    countPic = 1;
    for (int i = 0; i < countPic; ++i)
    {
        QMovie* dummy = new QMovie("Resources/plants/sunflower/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/sunflower/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QSunflower::~QSunflower()
{

}

bool QSunflower::canAttack(QUnit *)
{
    return false;
}

std::vector<QWeapon*> QSunflower::attack()
{
    std::vector<QWeapon*> weapons;
    return weapons;
}

bool QSunflower::canGenerateSunshine()
{
    if (cd <= 0 && clicked) return true;
    return false;
}

QSunshine* QSunflower::generateSunshine(int _id)
{
    clicked = false;
    return new QSunshine(_id);
}

bool QSunflower::isMushroom()
{
    return false;
}

bool QSunflower::canLitUp()
{
    return false;
}

void QSunflower::updateInfo()
{

}

