#include "qpuffshroom.h"

QPuffShroom::QPuffShroom(int _id)
{
    id = _id;
    hp = baseHp = 300;
    cd = baseCd = 1.4 * 1000 / TIME_ELAPSE;
    rng = baserng = 99999999;
    bullet = 99999999;
    shell = 0;
    spdX = spdY = baseSpdX = baseSpdY = 0;
    weapon = new QMushroomWeapon();

    countPic = 1;
    for (int i = 0; i < countPic; ++i)
    {
        QMovie* dummy = new QMovie("Resources/plants/puffshroom/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/puffshroom/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QPuffShroom::~QPuffShroom()
{

}

bool QPuffShroom::canAttack(QUnit* unit)
{
    if (cd > 0) return false;
    if (unit->pos().x() + unit->width() / 2 > WINDOW_WIDTH || unit->pos().x() + unit->width() / 2 < this->pos().x()) return false;
    if (abs(this->pos().y() + this->height() - unit->pos().y() - unit->height()) > 1) return false;
    if (unit->getCenter().x() - this->pos().x() > 280) return false;
    return true;
}

std::vector<QWeapon*> QPuffShroom::attack()
{
    ++shell;
    std::vector<QWeapon*> weapons;
    QWeapon* wp = new QMushroomWeapon();
    wp->setAxis(this->pos().x() + this->width() / 3, this->pos().y() + this->height());
    weapons.push_back(wp);
    cd = baseCd;
    return weapons;
}

bool QPuffShroom::canGenerateSunshine()
{
    return false;
}

QSunshine* QPuffShroom::generateSunshine(int _id)
{
    return nullptr;
}

bool QPuffShroom::isMushroom()
{
    return false;
}

bool QPuffShroom::canLitUp()
{
    return false;
}

void QPuffShroom::updateInfo()
{
    --cd;
}


