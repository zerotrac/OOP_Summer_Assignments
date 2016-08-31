#include "QSnowPea.h"

QSnowPea::QSnowPea(int _id)
{
    id = _id;
    atk = baseAtk = 20;
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
        QMovie* dummy = new QMovie("Resources/plants/snowpea/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/snowpea/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QSnowPea::~QSnowPea()
{

}

bool QSnowPea::canAttack()
{
    if (cd <= 0) return true;
    return false;
}

std::vector<QWeapon*> QSnowPea::attack()
{
    ++shell;
    std::vector<QWeapon*> weapons;
    weapons.push_back(new QPeaWeapon(0));
    cd = baseCd;
    return weapons;
}

bool QSnowPea::canGenerateSunshine()
{
    return false;
}

QSunshine* QSnowPea::generateSunshine()
{
    return nullptr;
}

bool QSnowPea::isMushroom()
{
    return false;
}

bool QSnowPea::canLitUp()
{
    return false;
}

void QSnowPea::updateInfo()
{
    --cd;
}
