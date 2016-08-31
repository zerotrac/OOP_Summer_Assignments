#ifndef QPEAWEAPON_H
#define QPEAWEAPON_H

#include "qweapon.h"

class QPeaWeapon: public QWeapon
{
public:
    QPeaWeapon(int _currentPic);
    virtual ~QPeaWeapon();

public:
    virtual bool inRange(QUnit *unit);
};

#endif // QPEAWEAPON_H
