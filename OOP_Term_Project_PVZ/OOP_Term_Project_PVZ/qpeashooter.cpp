#include "qpeashooter.h"

QPeashooter::QPeashooter(int _id)
{
    id = _id;
    atk = baseAtk = 20;
    hp = baseHp = 300;
    cd = baseCd = 7.5 * 1000 / TIME_ELAPSE;
    rng = baserng = 99999999;
    bullet = 99999999;
    shell = 0;
    spdX = spdY = baseSpdX = baseSpdY = 0;
    weapon = nullptr;

    countPic = 1;
    for (int i = 0; i < countPic; ++i)
    {
        QMovie* dummy = new QMovie("Resources/plants/peashooter/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/peashooter/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QPeashooter::~QPeashooter()
{

}

bool QPeashooter::canAttack()
{
    return false;
}

std::vector<QWeapon*> QPeashooter::attack()
{
    std::vector<QWeapon*> weapons;
    return weapons;
}

bool QPeashooter::canGenerateSunshine()
{
    return false;
}

QSunshine* QPeashooter::generateSunshine()
{
    return nullptr;
}

bool QPeashooter::isMushroom()
{
    return false;
}

void QPeashooter::updateInfo()
{
    --cd;
}
