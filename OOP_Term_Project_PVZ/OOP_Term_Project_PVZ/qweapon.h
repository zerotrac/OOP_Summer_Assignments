#ifndef QWEAPON_H
#define QWEAPON_H

#include <QLabel>
#include <QPixmap>
#include <vector>
#include "const.h"
#include "qunit.h"

class QUnit;
class QWeapon : public QLabel
{
    Q_OBJECT

public:
    QWeapon();
    virtual ~QWeapon();

protected:
    int duration; // 持续时间
    int bullet;
    int litID = -1;
    double spdX;
    double spdY;

    std::vector<QPixmap> pics;
    int countPic;
    int currentPic;

public:
    virtual bool inRange(QUnit* unit) = 0;
    bool outofDuration();
    void updateInfo();
    void setAxis(double dx, double dy);
    void setLit(int _litID);
};

#endif // QWEAPON_H
