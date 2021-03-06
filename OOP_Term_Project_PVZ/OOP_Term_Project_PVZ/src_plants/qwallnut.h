#ifndef QWALLNUT_H
#define QWALLNUT_H

#include "qplant.h"
#include "qweapon.h"

class QWallnut: public QPlant
{
    Q_OBJECT

public:
    QWallnut(int _id);
    virtual ~QWallnut();

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

#endif // QWALLNUT_H
