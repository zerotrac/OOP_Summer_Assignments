#include "qcommonzombie.h"

QCommonZombie::QCommonZombie(int _id)
{
    id = _id;
    hp = baseHp = 200;
    cd = baseCd = 1;
    rng = baserng = 40;
    bullet = 99999999;
    shell = 0;
    spdX = baseSpdX = -80.0 / (4.7 * 1000 / TIME_ELAPSE);
    weapon = nullptr;

    countPic = 4;
    for (int i = 0; i < countPic; ++i)
    {
        QMovie* dummy = new QMovie("Resources/zombies/commonzombie/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/zombies/commonzombie/0.gif").size());
    this->setMovie(pics[currentPic]);

    hpS = 0.40;
    hpL = 0.30;
}

QCommonZombie::~QCommonZombie()
{

}

bool QCommonZombie::canAttack(QUnit *unit)
{
    return false;
}

std::vector<QWeapon*> QCommonZombie::attack()
{
    std::vector<QWeapon*> weapons;
    return weapons;
}

void QCommonZombie::updateInfo()
{
    --cd;
    posX += spdX;
    this->setGeometry(posX, posY, 0, 0);
    if (hp <= 20)
    {
        currentPic = 2;
        this->setMovie(pics[currentPic]);
    }
    this->update();
}

QPoint QCommonZombie::getCenter() const
{
    return QPoint(this->pos().x() + this->width() / 2, this->pos().y() + this->height() / 2);
}
