#ifndef QTORCHWOOD_H
#define QTORCHWOOD_H

#include "qplant.h"
#include "qweapon.h"

class QTorchwood: public QPlant
{
    Q_OBJECT

public:
    QTorchwood(int _id);
    virtual ~QTorchwood();

public:
    virtual bool canAttack();
    virtual std::vector<QWeapon*> attack();
    virtual bool canGenerateSunshine();
    virtual QSunshine* generateSunshine();
    virtual bool isMushroom();
    virtual bool canLitUp();
    virtual void updateInfo();
};

#endif // QTORCHWOOD_H
