#ifndef QCOMMONZOMBIE_H
#define QCOMMONZOMBIE_H

#include "qzombie.h"
#include "qweapon.h"

class QCommonZombie: public QZombie
{
    Q_OBJECT

public:
    QCommonZombie(int _id);
    virtual ~QCommonZombie();

public:
    virtual bool canAttack(QUnit*);
    virtual std::vector<QWeapon*> attack();
    virtual void updateInfo();
    virtual QPoint getCenter() const;
};

#endif // QCOMMONZOMBIE_H
