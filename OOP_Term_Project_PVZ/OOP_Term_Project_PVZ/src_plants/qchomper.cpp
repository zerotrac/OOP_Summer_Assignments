#include "qchomper.h"

QChomper::QChomper(int _id)
{
    id = _id;
    hp = baseHp = 300;
    cd = 1000 / TIME_ELAPSE;
    baseCd = 42 * 1000 / TIME_ELAPSE;
    rng = baserng = 0;
    bullet = 99999999;
    shell = 0;
    spdX = spdY = baseSpdX = baseSpdY = 0;
    weapon = new QHandWeapon(99999999);

    countPic = 3;
    for (int i = 0; i < countPic; ++i)
    {
        QMovie* dummy = new QMovie("Resources/plants/chomper/" + QString::number(i) + ".gif");
        if (i != 1) dummy->start();
        dummy->setSpeed(200);
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/chomper/0.gif").size());
    this->setMovie(pics[currentPic]);

    QObject::connect(pics[1], SIGNAL(finished()), this, SLOT(slotPic2()));
}

QChomper::~QChomper()
{

}

bool QChomper::canAttack(QUnit* unit)
{
    if (cd > 0) return false;
    if (unit->pos().x() + unit->width() / 2 > WINDOW_WIDTH || unit->pos().x() + unit->width() < this->pos().x()) return false;
    if (abs(this->pos().y() + this->height() - unit->pos().y() - unit->height()) > 1) return false;
    if (unit->getCenter().x() - this->getCenter().x() > 40) return false;
    return true;
}

std::vector<QWeapon*> QChomper::attack()
{
    ++shell;
    std::vector<QWeapon*> weapons;
    QWeapon* wp = new QHandWeapon(99999999);
    wp->setFixedSize(40, 10);
    wp->setAxis(this->pos().x() + this->width() / 2, this->pos().y() + this->height() / 2);
    weapons.push_back(wp);
    cd = baseCd;

    currentPic = 1;
    pics[currentPic]->jumpToFrame(0);
    pics[currentPic]->start();
    this->setMovie(pics[currentPic]);

    return weapons;
}

bool QChomper::canGenerateSunshine()
{
    return false;
}

QSunshine* QChomper::generateSunshine(int _id)
{
    return nullptr;
}

bool QChomper::isMushroom()
{
    return false;
}

bool QChomper::canLitUp()
{
    return false;
}

void QChomper::updateInfo()
{
    --cd;
    if (cd <= 0)
    {
        currentPic = 0;
        this->setMovie(pics[currentPic]);
    }
}

void QChomper::slotPic2()
{
    currentPic = 2;
    this->setMovie(pics[currentPic]);
}
