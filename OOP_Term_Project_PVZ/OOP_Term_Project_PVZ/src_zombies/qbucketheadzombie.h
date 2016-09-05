#ifndef QBUCKETHEADZOMBIE_H
#define QBUCKETHEADZOMBIE_H

#include "qzombie.h"
#include "src_weapons/qhandweapon.h"

class QBucketHeadZombie: public QZombie
{
    Q_OBJECT

public:
    QBucketHeadZombie(int _id);
    virtual ~QBucketHeadZombie();

public:
    virtual bool canAttack(QUnit*);
    virtual std::vector<QWeapon*> attack();
    virtual void updateInfo();
    virtual QPoint getCenter() const;
};

#endif // QBUCKETHEADZOMBIE_H
