#ifndef QGAMEDAYINTERFACE_H
#define QGAMEDAYINTERFACE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QDebug>
#include <vector>
#include <unordered_set>
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
    std::unordered_set<int> plantsID;
    std::unordered_set<int> enemiesID;
    std::unordered_set<QWeapon*> weapons;
    std::vector<QPlant*> plants;
    std::vector<QPlant*> enemies;
    int plantLabel;
    int enemyLabel;

    int timerID;

private:
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent *event);
    QString getSplitColor(double per);

private:
    Ui::QGameDayInterface *ui;
};

#endif // QGAMEDAYINTERFACE_H
