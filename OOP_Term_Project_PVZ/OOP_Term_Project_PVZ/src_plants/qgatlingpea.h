#ifndef QGATLINGPEA_H
#define QGATLINGPEA_H

#include "qplant.h"
#include "src_weapons/qpeaweapon.h"

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
    virtual QSunshine* generateSunshine(int _id);
    virtual bool isMushroom();
    virtual bool canLitUp();
    virtual void updateInfo();
    virtual void setClicked() {}
};

#endif // QGATLINGPEA_H
