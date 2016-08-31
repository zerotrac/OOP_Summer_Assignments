#include "qweapon.h"

QWeapon::QWeapon(QObject *parent) : QObject(parent)
{

}

QWeapon::~QWeapon()
{

}

bool QWeapon::outofDuration()
{
    return (duration == 0 || posX < 0 || posX > WINDOW_WIDTH || posY < 0 || posY > WINDOW_WIDTH);
}
