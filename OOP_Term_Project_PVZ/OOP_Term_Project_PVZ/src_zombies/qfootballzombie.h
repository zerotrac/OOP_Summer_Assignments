#ifndef QFOOTBALLZOMBIE_H
#define QFOOTBALLZOMBIE_H

#include "qzombie.h"
#include "src_weapons/qhandweapon.h"

class QFootballZombie: public QZombie
{
    Q_OBJECT

public:
    QFootballZombie(int _id);
    virtual ~QFootballZombie();

public:
    virtual bool canAttack(QUnit*);
    virtual std::vector<QWeapon*> attack();
    virtual void updateInfo();
    virtual QPoint getCenter() const;
};

#endif // QFOOTBALLZOMBIE_H
