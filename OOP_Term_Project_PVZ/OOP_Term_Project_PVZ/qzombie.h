#ifndef QZOMBIE_H
#define QZOMBIE_H

#include "qunit.h"
#include "qweapon.h"

class QZombie: public QUnit
{
    Q_OBJECT

public:
    QZombie();
    virtual ~QZombie();

private:
    int freezeDebuff; // 僵尸被冰冻，移动速度减少50%
    int stunDebuff; // 僵尸被眩晕，移动速度为0
    int rageBuff; // 僵尸发怒了，移动速度变快

public:
    virtual bool canAttack() = 0;
    virtual std::vector<QWeapon*> attack() = 0;
    virtual bool isPlant();
    virtual bool isZombie();
    virtual void updateInfo() = 0;
};

#endif // QZOMBIE_H
