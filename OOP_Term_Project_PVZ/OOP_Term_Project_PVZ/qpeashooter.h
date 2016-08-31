#ifndef QPEASHOOTER_H
#define QPEASHOOTER_H

#include "qplant.h"

class QPeashooter: public QPlant
{
    Q_OBJECT

public:
    QPeashooter(int _id);
    virtual ~QPeashooter();

public:
    virtual bool canAttack();
    virtual std::vector<QWeapon*> attack();
    virtual bool canGenerateSunshine();
    virtual QSunshine* generateSunshine();
    virtual bool isMushroom();
    virtual void updateInfo();
};

#endif // QPEASHOOTER_H
