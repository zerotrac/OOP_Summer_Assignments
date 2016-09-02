#ifndef QPEASHOOTER_H
#define QPEASHOOTER_H

#include "qplant.h"
#include "src_weapons/qpeaweapon.h"

class QPeashooter: public QPlant
{
    Q_OBJECT

public:
    QPeashooter(int _id);
    virtual ~QPeashooter();

public:
    virtual bool canAttack(QUnit*);
    virtual std::vector<QWeapon*> attack();
    virtual bool canGenerateSunshine();
    virtual QSunshine* generateSunshine(int _id);
    virtual bool isMushroom();
    virtual bool canLitUp();
    virtual void updateInfo();
    virtual void setClicked() {}
};

#endif // QPEASHOOTER_H
