#ifndef QGAMEDAYINTERFACE_H
#define QGAMEDAYINTERFACE_H

#include <QWidget>
#include <vector>
#include <unordered_set>
#include <QTimerEvent>
#include "qpeashooter.h"
#include "qsnowpea.h"
#include "qdoublepea.h"
#include "qgatlingpea.h"
#include "qtorchwood.h"
#include "qwallnut.h"
#include "qplant.h"
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
    //QPlant* plants[11];
    std::unordered_set<QPlant*> plants;
    std::unordered_set<QPlant*> enemies;
    std::unordered_set<QWeapon*> weapons;
    int timerID;

private:
    void timerEvent(QTimerEvent *event);

private:
    Ui::QGameDayInterface *ui;
};

#endif // QGAMEDAYINTERFACE_H
