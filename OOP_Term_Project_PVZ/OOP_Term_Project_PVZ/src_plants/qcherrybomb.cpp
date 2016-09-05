#include "qcherrybomb.h"

QCherryBomb::QCherryBomb(int _id)
{
    id = _id;
    hp = baseHp = 300;
    cd = baseCd = 1 * 1000 / TIME_ELAPSE;
    rng = baserng = 99999999;
    bullet = 1;
    shell = 0;
    spdX = spdY = baseSpdX = baseSpdY = 0;
    weapon = new QCherryWeapon();

    countPic = 1;
    for (int i = 0; i < countPic; ++i)
    {
        QMovie* dummy = new QMovie("Resources/plants/cherrybomb/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/cherrybomb/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QCherryBomb::~QCherryBomb()
{

}

bool QCherryBomb::canAttack(QUnit* unit)
{
    if (cd > 0) return false;
    return true;
}

std::vector<QWeapon*> QCherryBomb::attack()
{
    ++shell;
    --bullet;
    std::vector<QWeapon*> weapons;
    QWeapon* wp = new QCherryWeapon();
    wp->setFixedSize(1, 1);
    wp->setAxis(this->getCenter().x(), this->getCenter().y());
    weapons.push_back(wp);
    cd = baseCd;
    return weapons;
}

bool QCherryBomb::canGenerateSunshine()
{
    return false;
}

QSunshine* QCherryBomb::generateSunshine(int _id)
{
    return nullptr;
}

bool QCherryBomb::isMushroom()
{
    return false;
}

bool QCherryBomb::canLitUp()
{
    return false;
}

void QCherryBomb::updateInfo()
{
    --cd;
    if (cd < 0) --bullet;
}
