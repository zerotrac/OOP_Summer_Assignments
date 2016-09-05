#ifndef QHANDWEAPON_H
#define QHANDWEAPON_H

#include "qweapon.h"

class QHandWeapon: public QWeapon
{
    Q_OBJECT

public:
    QHandWeapon(int _atk);
    virtual ~QHandWeapon();

public:
    virtual bool inRange(QUnit *unit);
    virtual void updateInfo();
};

#endif // QHANDWEAPON_H
