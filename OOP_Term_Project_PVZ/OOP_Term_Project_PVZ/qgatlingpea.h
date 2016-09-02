#ifndef QGATLINGPEA_H
#define QGATLINGPEA_H

#include "qplant.h"
#include "qpeaweapon.h"

class QGatlingPea: public QPlant
{
    Q_OBJECT

public:
    QGatlingPea(int _id);
    virtual ~QGatlingPea();

public:
    virtual bool canAttack(QUnit*);
    virtual std::vector<QWeapon*> attack();
    virtual bool canGenerateSunshine();
    virtual QSunshine* generateSunshine();
    virtual bool isMushroom();
    virtual bool canLitUp();
    virtual void updateInfo();
};

#endif // QGATLINGPEA_H
