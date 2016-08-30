#include "qplant.h"

QPlant::QPlant()
{

}

QPlant::~QPlant()
{

}

void QPlant::move()
{
    // 什么都不做
    // 因为植物无法移动
}

bool QPlant::isPlant()
{
    return true;
}

bool QPlant::isZombie()
{
    return false;
}
