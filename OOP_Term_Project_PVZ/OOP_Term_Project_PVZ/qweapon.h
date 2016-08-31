#ifndef QWEAPON_H
#define QWEAPON_H

#include <QObject>

class QWeapon : public QObject
{
    Q_OBJECT
public:
    explicit QWeapon(QObject *parent = 0);

};

#endif // QWEAPON_H
