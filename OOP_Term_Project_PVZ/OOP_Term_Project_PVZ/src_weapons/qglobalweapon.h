#ifndef QGLOBALWEAPON_H
#define QGLOBALWEAPON_H

#include "qweapon.h"

class QGlobalWeapon: public QWeapon
{
    Q_OBJECT

public:
    QGlobalWeapon();
    virtual ~QGlobalWeapon();

public:
    virtual bool inRange(QUnit *unit);
    virtual void updateInfo();
    virtual QBuff getBuff() const;
};

#endif // QGLOBALWEAPON_H
