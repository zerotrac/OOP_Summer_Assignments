#ifndef QPEAWEAPON_H
#define QPEAWEAPON_H

#include "qweapon.h"

class QPeaWeapon: public QWeapon
{
    Q_OBJECT

public:
    QPeaWeapon(int _currentPic);
    virtual ~QPeaWeapon();

public:
    virtual bool inRange(QUnit *unit);
    virtual void updateInfo();
    virtual QBuff getBuff() const;
};

#endif // QPEAWEAPON_H
