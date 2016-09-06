#include "qscaredyshroom.h"

QScaredyShroom::QScaredyShroom(int _id)
{
    id = _id;
    hp = baseHp = 300;
    cd = baseCd = 1.4 * 1000 / TIME_ELAPSE;
    rng = baserng = 99999999;
    bullet = 99999999;
    shell = 0;
    spdX = spdY = baseSpdX = baseSpdY = 0;
    weapon = new QMushroomWeapon();

    countPic = 2;
    for (int i = 0; i < countPic; ++i)
    {
        QMovie* dummy = new QMovie("Resources/plants/scaredyshroom/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/scaredyshroom/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QScaredyShroom::~QScaredyShroom()
{

}

bool QScaredyShroom::canAttack(QUnit* unit)
{
    if (cd > 0) return false;
    if (unit->pos().x() + unit->width() / 2 > WINDOW_WIDTH || unit->pos().x() + unit->width() / 2 < this->pos().x()) return false;
    if (abs(this->pos().y() + this->height() - unit->pos().y() - unit->height()) > 1) return false;
    if (unit->getCenter().x() - this->pos().x() < 120) scared = true;
    return true;
}

std::vector<QWeapon*> QScaredyShroom::attack()
{
    ++shell;
    std::vector<QWeapon*> weapons;
    if (scared) return weapons;

    QWeapon* wp = new QMushroomWeapon();
    wp->setAxis(this->pos().x() + this->width() / 3, this->pos().y() + this->height() / 6 * 5);
    weapons.push_back(wp);
    cd = baseCd;
    return weapons;
}

bool QScaredyShroom::canGenerateSunshine()
{
    return false;
}

QSunshine* QScaredyShroom::generateSunshine(int _id)
{
    return nullptr;
}

bool QScaredyShroom::isMushroom()
{
    return false;
}

bool QScaredyShroom::canLitUp()
{
    return false;
}

void QScaredyShroom::updateInfo()
{
    --cd;
    if (scared) currentPic = 1; else currentPic = 0;
    this->setMovie(pics[currentPic]);
    scared = false;
}
