#ifndef QCHERRYBOMB_H
#define QCHERRYBOMB_H

#include "qplant.h"
#include "src_weapons/qcherryweapon.h"

class QCherryBomb: public QPlant
{
    Q_OBJECT

public:
    QCherryBomb(int _id);
    virtual ~QCherryBomb();

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

#endif // QCHERRYBOMB_H
