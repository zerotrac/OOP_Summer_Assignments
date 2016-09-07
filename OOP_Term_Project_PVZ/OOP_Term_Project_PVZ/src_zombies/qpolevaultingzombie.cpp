#include "qpolevaultingzombie.h"

QPoleVaultingZombie::QPoleVaultingZombie(int _id)
{
    id = _id;
    hp = baseHp = 340;
    cd = baseCd = 1;
    rng = baserng = 40;
    bullet = 99999999;
    shell = 0;
    spdX = baseSpdX = -80.0 / (2.5 * 1000 / TIME_ELAPSE);
    weapon = nullptr;

    countPic = 7;
    for (int i = 0; i < 7; ++i)
    {
        QMovie* dummy = new QMovie("Resources/zombies/polevaultingzombie/" + QString::number(i) + ".gif");
        if (i != 2 && i != 3) dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/zombies/polevaultingzombie/0.gif").size());
    this->setMovie(pics[currentPic]);

    hpS = 0.60;
    hpL = 0.20;
    attacked = false;

    QObject::connect(pics[2], SIGNAL(finished()), this, SLOT(slotFin2()));
    QObject::connect(pics[3], SIGNAL(finished()), this, SLOT(slotFin3()));
}

QPoleVaultingZombie::~QPoleVaultingZombie()
{

}

bool QPoleVaultingZombie::canAttack(QUnit *unit)
{
    if (cd > 0) return false;
    if (unit->pos().x() > this->pos().x() + this->width()) return false;
    QPoint point1 = this->getCenter();
    QPoint point2 = unit->getCenter();
    if (std::fabs(this->pos().y() + this->height() - unit->pos().y() - unit->height()) > 0.1) return false;
    if (std::fabs(point1.x() - point2.x()) > rng) return false;
    return true;
}

std::vector<QWeapon*> QPoleVaultingZombie::attack()
{
    std::vector<QWeapon*> weapons;
    if (!lost)
    {
        if (currentPic == 0)
        {
            currentPic = 2;
            pics[currentPic]->start();
            this->setMovie(pics[currentPic]);
            spdX = baseSpdX = 0;
        }
        return weapons;
    }
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

void QPoleVaultingZombie::updateInfo()
{
    --cd;
    if (attacked)
    {
        if (hp <= 20)
        {
            currentPic = 7;
        }
        else
        {
            currentPic = 5;
        }
    }
    else
    {
        if (hp <= 20)
        {
            if (lost) currentPic = 6; else if (currentPic == 0) currentPic = 1;
        }
        else if (currentPic > 3)
        {
            currentPic = 4;
        }
        posX += spdX;
        this->setGeometry(posX, posY, 0, 0);
    }
    this->setMovie(pics[currentPic]);
    this->updateBuff();
    this->update();
    attacked = false;
}

QPoint QPoleVaultingZombie::getCenter() const
{
    return QPoint(this->pos().x() + this->width() / 3 * 2, this->pos().y() + this->height() / 4 * 3);
}

void QPoleVaultingZombie::slotFin2()
{
    currentPic = 3;
    pics[currentPic]->start();
    posX -= 125;
    this->setGeometry(posX, posY, 0, 0);
    this->setMovie(pics[currentPic]);
}

void QPoleVaultingZombie::slotFin3()
{
    currentPic = 4;
    this->setMovie(pics[currentPic]);
    lost = true;
    spdX = baseSpdX = -80.0 / (4.7 * 1000 / TIME_ELAPSE);
}
