#include "qpeashooter.h"

QPeashooter::QPeashooter(int _id)
{
    id = _id;
    hp = baseHp = 300;
    cd = baseCd = 1.4 * 1000 / TIME_ELAPSE;
    rng = baserng = 99999999;
    bullet = 99999999;
    shell = 0;
    spdX = spdY = baseSpdX = baseSpdY = 0;
    weapon = new QPeaWeapon(1);

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

bool QPeashooter::canAttack(QUnit* unit)
{
    if (cd > 0) return false;
    if (abs(this->pos().y() + this->height() - unit->pos().y() - unit->height()) < 0.1) return true;
    return false;
}

std::vector<QWeapon*> QPeashooter::attack()
{
    ++shell;
    std::vector<QWeapon*> weapons;
    weapons.push_back(new QPeaWeapon(1));
    cd = baseCd;
    return weapons;
}

bool QPeashooter::canGenerateSunshine()
{
    return false;
}

QSunshine* QPeashooter::generateSunshine(int _id)
{
    return nullptr;
}

bool QPeashooter::isMushroom()
{
    return false;
}

bool QPeashooter::canLitUp()
{
    return false;
}

void QPeashooter::updateInfo()
{
    --cd;
}
