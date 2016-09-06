#include "qjalapeno.h"

QJalapeno::QJalapeno(int _id)
{
    id = _id;
    hp = baseHp = 300;
    cd = baseCd = 1 * 1000 / TIME_ELAPSE;
    rng = baserng = 99999999;
    bullet = 1;
    shell = 0;
    spdX = spdY = baseSpdX = baseSpdY = 0;
    weapon = new QJalapenoWeapon();

    countPic = 1;
    for (int i = 0; i < countPic; ++i)
    {
        QMovie* dummy = new QMovie("Resources/plants/jalapeno/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/jalapeno/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QJalapeno::~QJalapeno()
{

}

bool QJalapeno::canAttack(QUnit* unit)
{
    if (cd > 0) return false;
    return true;
}

std::vector<QWeapon*> QJalapeno::attack()
{
    ++shell;
    --bullet;
    std::vector<QWeapon*> weapons;
    QWeapon* wp = new QJalapenoWeapon();
    wp->setFixedSize(1, 1);
    wp->setAxis(this->getCenter().x(), this->getCenter().y());
    weapons.push_back(wp);
    cd = baseCd;
    return weapons;
}

bool QJalapeno::canGenerateSunshine()
{
    return false;
}

QSunshine* QJalapeno::generateSunshine(int _id)
{
    return nullptr;
}

bool QJalapeno::isMushroom()
{
    return false;
}

bool QJalapeno::canLitUp()
{
    return false;
}

void QJalapeno::updateInfo()
{
    --cd;
    if (cd < 0) --bullet;
}


