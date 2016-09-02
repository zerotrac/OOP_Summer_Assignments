#ifndef QSUNFLOWER_H
#define QSUNFLOWER_H

#include "qplant.h"
#include "qweapon.h"
#include "qsunshine.h"

class QSunflower: public QPlant
{
    Q_OBJECT

public:
    QSunflower(int _id);
    virtual ~QSunflower();

private:
    bool clicked;

public:
    virtual bool canAttack(QUnit*);
    virtual std::vector<QWeapon*> attack();
    virtual bool canGenerateSunshine();
    virtual QSunshine* generateSunshine(int _id);
    virtual bool isMushroom();
    virtual bool canLitUp();
    virtual void updateInfo();
    void setClicked();
};

#endif // QSUNFLOWER_H
