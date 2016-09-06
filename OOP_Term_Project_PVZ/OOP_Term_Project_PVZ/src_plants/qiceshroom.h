#ifndef QICESHROOM_H
#define QICESHROOM_H

#include "qplant.h"
#include "src_weapons/qglobalweapon.h"

class QIceShroom: public QPlant
{
    Q_OBJECT

public:
    QIceShroom(int _id);
    virtual ~QIceShroom();

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

#endif // QICESHROOM_H
