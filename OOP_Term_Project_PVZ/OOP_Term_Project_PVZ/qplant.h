#ifndef QPLANT_H
#define QPLANT_H

#include <vector>
#include "qunit.h"
#include "qsunshine.h"

class QPlant: public QUnit
{
    Q_OBJECT

public:
    QPlant();
    virtual ~QPlant();

public:
    virtual bool canAttack(QUnit*) = 0;
    virtual std::vector<QWeapon*> attack() = 0;
    virtual bool isPlant();
    virtual bool isZombie();
    virtual bool canGenerateSunshine() = 0; // 是否是阳光类植物
    virtual QSunshine* generateSunshine(int _id) = 0; // 生成阳光
    virtual bool isMushroom() = 0; // 是否是蘑菇（蘑菇类只有在晚上可以使用）
    virtual bool canLitUp() = 0; // 判断是不是火炬树桩
    virtual void updateInfo() = 0;
};

#endif // QPLANT_H
