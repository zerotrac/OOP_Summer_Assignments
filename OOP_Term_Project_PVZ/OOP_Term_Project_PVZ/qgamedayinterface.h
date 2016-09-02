#ifndef QGAMEDAYINTERFACE_H
#define QGAMEDAYINTERFACE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QSignalMapper>
#include <QDebug>
#include <vector>
#include <unordered_set>
#include "qplant.h"
#include "qzombie.h"
#include "qweapon.h"
#include "qsunshine.h"
#include "src_plants/qpeashooter.h"
#include "src_plants/qsnowpea.h"
#include "src_plants/qdoublepea.h"
#include "src_plants/qgatlingpea.h"
#include "src_plants/qtorchwood.h"
#include "src_plants/qwallnut.h"

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
    std::unordered_set<int> sunshinesID;

    std::unordered_set<QWeapon*> weapons;
    std::vector<QPlant*> plants;
    std::vector<QPlant*> enemies;
    std::vector<QSunshine*> sunshines;

    QSignalMapper* sunshineMapper;
    int plantLabel;
    int enemyLabel;
    int sunshineLabel;

    int timerID;

private:
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent *event);
    QString getSplitColor(double per);

private:
    Ui::QGameDayInterface *ui;
};

#endif // QGAMEDAYINTERFACE_H
