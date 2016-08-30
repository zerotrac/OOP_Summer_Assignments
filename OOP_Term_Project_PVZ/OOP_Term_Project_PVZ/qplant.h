#ifndef QPLANT_H
#define QPLANT_H

#include "qunit.h"

class QPlant: public QUnit
{
    Q_OBJECT

public:
    QPlant();
    virtual ~QPlant();

public:
    virtual bool canAttack() = 0;
    virtual QWeapon* attack() = 0;
    virtual void move();
    virtual bool isPlant();
    virtual bool isZombie();
    virtual bool canGenerateSunshine() = 0; // 是否是阳光类植物
    virtual QSunshine* generateSunshine() = 0; // 生成阳光
    virtual bool isMushroom() = 0; // 是否是蘑菇（蘑菇类只有在晚上可以使用）
    virtual void updateInfo() = 0;
};

#endif // QPLANT_H
