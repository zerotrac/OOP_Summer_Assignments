#ifndef QPOTATOMINE_H
#define QPOTATOMINE_H

#include "qplant.h"
#include "src_weapons/qhandweapon.h"

class QPotatoMine: public QPlant
{
    Q_OBJECT

public:
    QPotatoMine(int _id);
    virtual ~QPotatoMine();

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

#endif // QPOTATOMINE_H
