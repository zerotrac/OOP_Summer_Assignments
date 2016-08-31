#include "qunit.h"

QUnit::QUnit()
{

}

QUnit::~QUnit()
{

}

void QUnit::move()
{
    posX += spdX;
    posY += spdY;
}

bool QUnit::isDead()
{
    return (hp == 0 || bullet == 0);
}
