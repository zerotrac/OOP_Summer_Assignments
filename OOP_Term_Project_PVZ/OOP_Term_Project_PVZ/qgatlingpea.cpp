#include "qgatlingpea.h"

QGatlingPea::QGatlingPea(int _id)
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

bool QGatlingPea::canAttack()
{
    if (cd <= 0) return true;
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

QSunshine* QGatlingPea::generateSunshine()
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
