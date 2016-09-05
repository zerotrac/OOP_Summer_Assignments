#ifndef QCOREHEADZOMBIE_H
#define QCOREHEADZOMBIE_H

#include "qzombie.h"
#include "src_weapons/qhandweapon.h"

class QConeHeadZombie: public QZombie
{
    Q_OBJECT

public:
    QConeHeadZombie(int _id);
    virtual ~QConeHeadZombie();

public:
    virtual bool canAttack(QUnit*);
    virtual std::vector<QWeapon*> attack();
    virtual void updateInfo();
    virtual QPoint getCenter() const;
};

#endif // QCONEHEADZOMBIE_H
