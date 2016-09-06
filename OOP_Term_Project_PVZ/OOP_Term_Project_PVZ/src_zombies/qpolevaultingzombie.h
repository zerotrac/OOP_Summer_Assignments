#ifndef QPOLEVAULTINGZOMBIE_H
#define QPOLEVAULTINGZOMBIE_H

#include "qzombie.h"
#include "src_weapons/qhandweapon.h"

class QPoleVaultingZombie: public QZombie
{
    Q_OBJECT

public:
    QPoleVaultingZombie(int _id);
    virtual ~QPoleVaultingZombie();

private:
    bool lost = false;

public:
    virtual bool canAttack(QUnit*);
    virtual std::vector<QWeapon*> attack();
    virtual void updateInfo();
    virtual QPoint getCenter() const;

private slots:
    void slotFin2();
    void slotFin3();
};

#endif // QPOLEVAULTINGZOMBIE_H
