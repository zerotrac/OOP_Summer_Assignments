#ifndef QSNOWPEA_H
#define QSNOWPEA_H

#include "qplant.h"
#include "qpeaweapon.h"

class QSnowPea: public QPlant
{
    Q_OBJECT

public:
    QSnowPea(int _id);
    virtual ~QSnowPea();

public:
    virtual bool canAttack();
    virtual std::vector<QWeapon*> attack();
    virtual bool canGenerateSunshine();
    virtual QSunshine* generateSunshine();
    virtual bool isMushroom();
    virtual bool canLitUp();
    virtual void updateInfo();
};

#endif // QSNOWPEA_H
