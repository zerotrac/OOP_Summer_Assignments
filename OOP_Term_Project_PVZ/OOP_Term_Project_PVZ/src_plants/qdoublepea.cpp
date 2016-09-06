#include "qdoublepea.h"

QDoublePea::QDoublePea(int _id)
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
        QMovie* dummy = new QMovie("Resources/plants/doublepea/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/doublepea/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QDoublePea::~QDoublePea()
{

}

bool QDoublePea::canAttack(QUnit* unit)
{
    if (cd > 0) return false;
    if (unit->pos().x() + unit->width() / 2 > WINDOW_WIDTH || unit->pos().x() + unit->width() < this->pos().x()) return false;
    if (abs(this->pos().y() + this->height() - unit->pos().y() - unit->height()) < 1) return true;
    return false;
}

std::vector<QWeapon*> QDoublePea::attack()
{
    ++shell;
    std::vector<QWeapon*> weapons;
    QWeapon* wp = new QPeaWeapon(1);
    wp->setAxis(this->pos().x() + this->width() / 3, this->pos().y() + this->height() / 2);
    weapons.push_back(wp);
    if (shell % 2 == 0) cd = baseCd; else cd = 0.2 * 1000 / TIME_ELAPSE;
    return weapons;
}

bool QDoublePea::canGenerateSunshine()
{
    return false;
}

QSunshine* QDoublePea::generateSunshine(int _id)
{
    return nullptr;
}

bool QDoublePea::isMushroom()
{
    return false;
}

bool QDoublePea::canLitUp()
{
    return false;
}

void QDoublePea::updateInfo()
{
    --cd;
}
