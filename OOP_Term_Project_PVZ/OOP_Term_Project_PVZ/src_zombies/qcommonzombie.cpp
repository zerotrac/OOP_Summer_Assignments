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
    attacked = false;
}

QCommonZombie::~QCommonZombie()
{

}

bool QCommonZombie::canAttack(QUnit *unit)
{
    if (cd > 0) return false;
    if (unit->pos().x() > this->pos().x() + this->width()) return false;
    QPoint point1 = this->getCenter();
    QPoint point2 = unit->getCenter();
    if (std::fabs(this->pos().y() + this->height() - unit->pos().y() - unit->height()) > 0.1) return false;
    if (std::fabs(point1.x() - point2.x()) > rng) return false;
    return true;
}

std::vector<QWeapon*> QCommonZombie::attack()
{
    std::vector<QWeapon*> weapons;
    QWeapon* wp = new QHandWeapon(100 / (1000 / TIME_ELAPSE));
    wp->setFixedSize(40, 10);
    QPoint point = this->getCenter();
    wp->setAxis(point.x() - 40, point.y() + 10);
    weapons.push_back(wp);
    cd = baseCd * 1;
    attacked = true;
    return weapons;
}

void QCommonZombie::updateInfo()
{
    --cd;
    if (attacked)
    {
        if (hp <= 20) currentPic = 3; else currentPic = 1;
    }
    else
    {
        if (hp <= 20) currentPic = 2; else currentPic = 0;
        posX += spdX;
        this->setGeometry(posX, posY, 0, 0);
    }
    this->setMovie(pics[currentPic]);
    this->updateBuff();
    this->update();
    attacked = false;
}

QPoint QCommonZombie::getCenter() const
{
    return QPoint(this->pos().x() + this->width() / 2, this->pos().y() + this->height() / 3 * 2);
}
