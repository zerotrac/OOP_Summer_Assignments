#ifndef QCHOMPER_H
#define QCHOMPER_H

#include "qplant.h"
#include "src_weapons/qhandweapon.h"

class QChomper: public QPlant
{
    Q_OBJECT

public:
    QChomper(int _id);
    virtual ~QChomper();

public:
    virtual bool canAttack(QUnit*);
    virtual std::vector<QWeapon*> attack();
    virtual bool canGenerateSunshine();
    virtual QSunshine* generateSunshine(int _id);
    virtual bool isMushroom();
    virtual bool canLitUp();
    virtual void updateInfo();
    virtual void setClicked() {}

private slots:
    void slotPic2();
};

#endif // QCHOMPER_H
