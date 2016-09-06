#include "qiceshroom.h"

QIceShroom::QIceShroom(int _id)
{
    id = _id;
    hp = baseHp = 300;
    cd = baseCd = 1 * 1000 / TIME_ELAPSE;
    rng = baserng = 99999999;
    bullet = 1;
    shell = 0;
    spdX = spdY = baseSpdX = baseSpdY = 0;
    weapon = new QGlobalWeapon();

    countPic = 1;
    for (int i = 0; i < countPic; ++i)
    {
        QMovie* dummy = new QMovie("Resources/plants/iceshroom/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/iceshroom/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QIceShroom::~QIceShroom()
{

}

bool QIceShroom::canAttack(QUnit* unit)
{
    if (cd > 0) return false;
    return true;
}

std::vector<QWeapon*> QIceShroom::attack()
{
    ++shell;
    --bullet;
    std::vector<QWeapon*> weapons;
    QWeapon* wp = new QGlobalWeapon();
    wp->setFixedSize(1, 1);
    wp->setAxis(this->getCenter().x(), this->getCenter().y());
    weapons.push_back(wp);
    cd = baseCd;
    return weapons;
}

bool QIceShroom::canGenerateSunshine()
{
    return false;
}

QSunshine* QIceShroom::generateSunshine(int _id)
{
    return nullptr;
}

bool QIceShroom::isMushroom()
{
    return false;
}

bool QIceShroom::canLitUp()
{
    return false;
}

void QIceShroom::updateInfo()
{
    --cd;
    if (cd < 0) --bullet;
}


