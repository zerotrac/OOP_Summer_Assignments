#include "qunit.h"

QUnit::QUnit()
{

}

QUnit::~QUnit()
{

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
