#ifndef QWEAPON_H
#define QWEAPON_H

#include <QObject>
#include <QPixmap>
#include <vector>
#include "const.h"

class QUnit;
class QWeapon : public QObject
{
    Q_OBJECT

public:
    explicit QWeapon(QObject *parent = 0);
    virtual ~QWeapon();

protected:
    int duration; // 持续时间
    double posX;
    double posY;
    double spdX;
    double spdY;

    std::vector<QPixmap> pics;
    int currentpic;

public:
    virtual bool inRange(QUnit* unit) = 0;
    bool outofDuration();
};

#endif // QWEAPON_H
