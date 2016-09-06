#include "qzombie.h"

QZombie::QZombie()
{
    freezeDebuff = 0;
    stunDebuff = 0;
    rageBuff = 0;

    spdY = 0.0;
    baseSpdY = 0.0;
}

QZombie::~QZombie()
{

}

bool QZombie::isPlant()
{
    return false;
}

bool QZombie::isZombie()
{
    return true;
}

void QZombie::setAxis(double dx, double dy)
{
    posX = dx;
    posY = dy - this->height();
    this->setGeometry(dx, dy - this->height(), 0, 0);
}

void QZombie::eatBuff(QBuff buff)
{
    freezeDebuff = std::max(freezeDebuff, buff.freezeDebuff);
    stunDebuff = std::max(stunDebuff, buff.stunDebuff);
}

void QZombie::updateBuff()
{
    //qDebug() << "buff =" << stunDebuff << freezeDebuff;
    if (stunDebuff > 0)
    {
        pics[currentPic]->stop();
        spdX = baseSpdX * 0;
    }
    else if (freezeDebuff > 0)
    {
        pics[currentPic]->start();
        pics[currentPic]->setSpeed(50);
        spdX = baseSpdX * 0.5;
    }
    else
    {
        pics[currentPic]->start();
        pics[currentPic]->setSpeed(100);
        spdX = baseSpdX * 1.0;
    }
    --freezeDebuff;
    --stunDebuff;
    --rageBuff;
}
