#ifndef QDOUBLEPEA_H
#define QDOUBLEPEA_H

#include "qplant.h"
#include "qpeaweapon.h"

class QDoublePea: public QPlant
{
    Q_OBJECT

public:
    QDoublePea(int _id);
    virtual ~QDoublePea();

public:
    virtual bool canAttack(QUnit*);
    virtual std::vector<QWeapon*> attack();
    virtual bool canGenerateSunshine();
    virtual QSunshine* generateSunshine(int _id);
    virtual bool isMushroom();
    virtual bool canLitUp();
    virtual void updateInfo();
};

#endif // QDOUBLEPEA_H
