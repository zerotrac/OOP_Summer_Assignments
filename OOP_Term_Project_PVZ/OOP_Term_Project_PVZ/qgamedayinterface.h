#ifndef QGAMEDAYINTERFACE_H
#define QGAMEDAYINTERFACE_H

#include <QWidget>
#include <vector>
#include <QTimerEvent>
#include "qpeashooter.h"
#include "qweapon.h"

namespace Ui {
class QGameDayInterface;
}

class QGameDayInterface : public QWidget
{
    Q_OBJECT

public:
    explicit QGameDayInterface(QWidget *parent = 0);
    ~QGameDayInterface();

private:
    QPeashooter* pea;
    std::vector<QWeapon*> weapons;
    int head = 0;
    int tail = -1;
    int timerID;

private:
    void timerEvent(QTimerEvent *event);

private:
    Ui::QGameDayInterface *ui;
};

#endif // QGAMEDAYINTERFACE_H
