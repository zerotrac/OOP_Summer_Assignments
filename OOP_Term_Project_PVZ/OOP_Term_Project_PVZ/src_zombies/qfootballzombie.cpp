#include "qfootballzombie.h"

QFootballZombie::QFootballZombie(int _id)
{
    id = _id;
    hp = baseHp = 1620;
    cd = baseCd = 1;
    rng = baserng = 40;
    bullet = 99999999;
    shell = 0;
    spdX = baseSpdX = -80.0 / (2.5 * 1000 / TIME_ELAPSE);
    weapon = nullptr;

    countPic = 6;
    for (int i = 0; i < 6; ++i)
    {
        QMovie* dummy = new QMovie("Resources/zombies/footballzombie/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/zombies/footballzombie/0.gif").size());
    this->setMovie(pics[currentPic]);

    hpS = 0.33;
    hpL = 0.33;
    attacked = false;
}

QFootballZombie::~QFootballZombie()
{

}

bool QFootballZombie::canAttack(QUnit *unit)
{
    if (cd > 0) return false;
    if (unit->pos().x() > this->pos().x() + this->width()) return false;
    QPoint point1 = this->getCenter();
    QPoint point2 = unit->getCenter();
    if (std::fabs(this->pos().y() + this->height() - unit->pos().y() - unit->height()) > 0.1) return false;
    if (std::fabs(point1.x() - point2.x()) > rng) return false;
    return true;
}

std::vector<QWeapon*> QFootballZombie::attack()
{
    std::vector<QWeapon*> weapons;
    QWeapon* wp = new QHandWeapon(100 / (1000 / TIME_ELAPSE));
    if (stunDebuff > 0) wp->atk = 0; else if (freezeDebuff > 0) wp->atk /= 2;
    wp->setFixedSize(40, 10);
    QPoint point = this->getCenter();
    wp->setAxis(point.x() - 40, point.y() + 10);
    weapons.push_back(wp);
    cd = baseCd * 1;
    attacked = true;
    return weapons;
}

void QFootballZombie::updateInfo()
{
    --cd;
    if (attacked)
    {
        if (hp <= 20) currentPic = 5; else if (hp <= 180) currentPic = 3; else currentPic = 1;
    }
    else
    {
        if (hp <= 20) currentPic = 4; else if (hp <= 180) currentPic = 2; else currentPic = 0;
        posX += spdX;
        this->setGeometry(posX, posY, 0, 0);
    }
    this->setMovie(pics[currentPic]);
    this->updateBuff();
    this->update();
    attacked = false;
}

QPoint QFootballZombie::getCenter() const
{
    return QPoint(this->pos().x() + this->width() / 3, this->pos().y() + this->height() / 3 * 2);
}
