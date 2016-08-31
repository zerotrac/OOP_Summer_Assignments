#ifndef QZOMBIE_H
#define QZOMBIE_H

#include "qunit.h"

class QZombie: public QUnit
{
    Q_OBJECT

public:
    QZombie();
    ~QZombie();

private:
    int freezeDebuff; // 僵尸被冰冻，移动速度减少50%，奇数帧不会动
    int stunDebuff; // 僵尸被眩晕，移动速度为0，所有帧都不会动
    int rageBuff; // 僵尸发怒了，移动速度变快

private:
    virtual bool canAttack() = 0;
    virtual QWeapon* attack() = 0;
    virtual bool isPlant();
    virtual bool isZombie();
    virtual bool canGenerateSunshine() = 0; // 是否是阳光类植物
    virtual bool isMushroom() = 0; // 是否是蘑菇（蘑菇类只有在晚上可以使用）
    virtual void updateInfo() = 0;
};

#endif // QZOMBIE_H
