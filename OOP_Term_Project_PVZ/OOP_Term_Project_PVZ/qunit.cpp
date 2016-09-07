#include "qunit.h"

QUnit::QUnit()
{
    this->setMouseTracking(true);
}

QUnit::~QUnit()
{
    delete weapon;
    for (int i = 0; i < countPic; ++i)
    {
        delete pics[i];
    }
    pics.clear();
}

void QUnit::move()
{
    this->setGeometry(this->pos().x() + spdX, this->pos().y() + spdY, 0, 0);
}

bool QUnit::isDead() const
{
    return (hp <= 0 || bullet <= 0);
}

void QUnit::setAxis(double dx, double dy)
{
    this->setGeometry(dx, dy - this->height(), 0, 0);
}

void QUnit::beAttacked(int damage)
{
    hp -= damage;
}

int QUnit::getCurrentHP() const
{
    return hp;
}

int QUnit::getMaxHP() const
{
    return baseHp;
}
