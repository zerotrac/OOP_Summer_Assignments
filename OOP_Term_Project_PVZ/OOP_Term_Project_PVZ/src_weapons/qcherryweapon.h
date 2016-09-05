#ifndef QCHERRYWEAPON_H
#define QCHERRYWEAPON_H

#include "qweapon.h"

class QCherryWeapon: public QWeapon
{
    Q_OBJECT

public:
    QCherryWeapon();
    virtual ~QCherryWeapon();

public:
    virtual bool inRange(QUnit *unit);
    virtual void updateInfo();
};

#endif // QCHERRYWEAPON_H
