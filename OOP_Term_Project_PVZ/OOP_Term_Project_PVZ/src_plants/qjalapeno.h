#ifndef QJALAPENO_H
#define QJALAPENO_H

#include "qplant.h"
#include "src_weapons/qjalapenoweapon.h"

class QJalapeno: public QPlant
{
    Q_OBJECT

public:
    QJalapeno(int _id);
    virtual ~QJalapeno();

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

#endif // QJALAPENO_H
