#ifndef QSCAREDYSHROOM_H
#define QSCAREDYSHROOM_H

#include "qplant.h"
#include "src_weapons/qmushroomweapon.h"

class QScaredyShroom: public QPlant
{
    Q_OBJECT

public:
    QScaredyShroom(int _id);
    virtual ~QScaredyShroom();

public:
    bool scared = false;

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

#endif // QSCAREDYSHROOM_H
