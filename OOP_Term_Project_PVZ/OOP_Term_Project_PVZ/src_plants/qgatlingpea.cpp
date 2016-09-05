#include "qgatlingpea.h"

QGatlingPea::QGatlingPea(int _id)
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
        QMovie* dummy = new QMovie("Resources/plants/gatlingpea/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/gatlingpea/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QGatlingPea::~QGatlingPea()
{

}

bool QGatlingPea::canAttack(QUnit* unit)
{
    if (cd > 0) return false;
    if (unit->pos().x() + unit->width() > WINDOW_WIDTH || unit->pos().x() + unit->width() < this->pos().x()) return false;
    if (abs(this->pos().y() + this->height() - unit->pos().y() - unit->height()) < 0.1) return true;
    return false;
}

std::vector<QWeapon*> QGatlingPea::attack()
{
    ++shell;
    std::vector<QWeapon*> weapons;
    weapons.push_back(new QPeaWeapon(1));
    if (shell % 4 == 0) cd = baseCd; else cd = 0.2 * 1000 / TIME_ELAPSE;
    return weapons;
}

bool QGatlingPea::canGenerateSunshine()
{
    return false;
}

QSunshine* QGatlingPea::generateSunshine(int _id)
{
    return nullptr;
}

bool QGatlingPea::isMushroom()
{
    return false;
}

bool QGatlingPea::canLitUp()
{
    return false;
}

void QGatlingPea::updateInfo()
{
    --cd;
}
