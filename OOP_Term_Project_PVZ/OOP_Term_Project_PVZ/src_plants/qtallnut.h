#ifndef QTALLNUT_H
#define QTALLNUT_H

#include "qplant.h"
#include "qweapon.h"

class QTallnut: public QPlant
{
    Q_OBJECT

public:
    QTallnut(int _id);
    virtual ~QTallnut();

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

#endif // QTALLNUT_H
