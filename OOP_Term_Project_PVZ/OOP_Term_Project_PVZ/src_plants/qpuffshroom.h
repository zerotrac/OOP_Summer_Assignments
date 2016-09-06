#ifndef QPUFFSHROOM_H
#define QPUFFSHROOM_H

#include "qplant.h"
#include "src_weapons/qmushroomweapon.h"

class QPuffShroom: public QPlant
{
    Q_OBJECT

public:
    QPuffShroom(int _id);
    virtual ~QPuffShroom();

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

#endif // QPUFFSHROOM_H
