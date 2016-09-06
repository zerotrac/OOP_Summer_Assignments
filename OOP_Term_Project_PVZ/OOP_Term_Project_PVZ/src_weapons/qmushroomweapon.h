#ifndef QMUSHROOMWEAPON_H
#define QMUSHROOMWEAPON_H

#include "qweapon.h"

class QMushroomWeapon: public QWeapon
{
    Q_OBJECT

public:
    QMushroomWeapon();
    virtual ~QMushroomWeapon();

public:
    virtual bool inRange(QUnit *unit);
    virtual void updateInfo();
};

#endif // QMUSHROOMWEAPON_H
