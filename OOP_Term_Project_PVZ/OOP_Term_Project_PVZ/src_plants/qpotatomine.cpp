#include "qpotatomine.h"

QPotatoMine::QPotatoMine(int _id)
{
    id = _id;
    hp = baseHp = 300;
    cd = baseCd = 16 * 1000 / TIME_ELAPSE;
    rng = baserng = 0;
    bullet = 1;
    shell = 0;
    spdX = spdY = baseSpdX = baseSpdY = 0;
    weapon = new QHandWeapon(99999999);

    countPic = 2;
    for (int i = 0; i < countPic; ++i)
    {
        QMovie* dummy = new QMovie("Resources/plants/potatomine/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/potatomine/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QPotatoMine::~QPotatoMine()
{

}

bool QPotatoMine::canAttack(QUnit* unit)
{
    if (cd > 0) return false;
    if (unit->pos().x() + unit->width() / 2 > WINDOW_WIDTH || unit->pos().x() + unit->width() < this->pos().x()) return false;
    if (abs(this->pos().y() + this->height() - unit->pos().y() - unit->height()) > 1) return false;
    if (unit->getCenter().x() - this->getCenter().x() > 40) return false;
    return true;
}

std::vector<QWeapon*> QPotatoMine::attack()
{
    ++shell;
    --bullet;
    std::vector<QWeapon*> weapons;
    QWeapon* wp = new QHandWeapon(99999999);
    wp->setFixedSize(40, 10);
    wp->setBullet(99999999);
    wp->setAxis(this->pos().x() + this->width() / 2, this->pos().y() + this->height() / 2);
    weapons.push_back(wp);
    cd = baseCd;

    return weapons;
}

bool QPotatoMine::canGenerateSunshine()
{
    return false;
}

QSunshine* QPotatoMine::generateSunshine(int _id)
{
    return nullptr;
}

bool QPotatoMine::isMushroom()
{
    return false;
}

bool QPotatoMine::canLitUp()
{
    return false;
}

void QPotatoMine::updateInfo()
{
    --cd;
    if (cd <= 0) currentPic = 1; else currentPic = 0;
    this->setMovie(pics[currentPic]);
}
