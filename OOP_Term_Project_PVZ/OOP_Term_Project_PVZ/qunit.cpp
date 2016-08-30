#include "qunit.h"

QUnit::QUnit(QObject *parent) : QObject(parent)
{

}

QUnit::~QUnit()
{

}


bool QUnit::isDead()
{
    return (hp == 0 || bullet == 0);
}
