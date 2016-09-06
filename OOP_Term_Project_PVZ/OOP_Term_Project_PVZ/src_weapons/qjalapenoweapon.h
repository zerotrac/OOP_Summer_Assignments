#ifndef QJALAPENOWEAPON_H
#define QJALAPENOWEAPON_H

#include "qweapon.h"

class QJalapenoWeapon: public QWeapon
{
    Q_OBJECT

public:
    QJalapenoWeapon();
    virtual ~QJalapenoWeapon();

public:
    virtual bool inRange(QUnit *unit);
    virtual void updateInfo();
};

#endif // QJALAPENOWEAPON_H
