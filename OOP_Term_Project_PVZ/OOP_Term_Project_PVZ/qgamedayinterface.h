#ifndef QGAMEDAYINTERFACE_H
#define QGAMEDAYINTERFACE_H

#include <QWidget>
#include <QCursor>
#include <QPainter>
#include <QEvent>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QSignalMapper>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QElapsedTimer>
#include <QTime>
#include <QFont>
#include <QDebug>
#include <vector>
#include <unordered_set>
#include "qplant.h"
#include "qzombie.h"
#include "qweapon.h"
#include "qsunshine.h"
#include "qcard.h"

#include "src_plants/qdoublepea.h"
#include "src_plants/qgatlingpea.h"
#include "src_plants/qpeashooter.h"
#include "src_plants/qsnowpea.h"
#include "src_plants/qsunflower.h"
#include "src_plants/qtorchwood.h"
#include "src_plants/qwallnut.h"
#include "src_plants/qtallnut.h"

#include "src_cards/qdoublepeacard.h"
#include "src_cards/qgatlingpeacard.h"
#include "src_cards/qpeashootercard.h"
#include "src_cards/qsnowpeacard.h"
#include "src_cards/qsunflowercard.h"
#include "src_cards/qtorchwoodcard.h"
#include "src_cards/qwallnutcard.h"
#include "src_cards/qtallnutcard.h"

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
    std::unordered_set<int> plantsID;
    std::unordered_set<int> enemiesID;
    std::unordered_set<int> sunshinesID;

    std::unordered_set<QWeapon*> weapons;
    std::vector<QPlant*> plants;
    std::vector<QPlant*> enemies;
    std::vector<QSunshine*> sunshines;

    QCard* cards[CARD_HEIGHT_COUNT][CARD_WIDTH_COUNT];
    QCard* cardsCanUse[CARD_CAN_USE];
    int cardsTop;

    QSignalMapper* sunshineMapper;
    QSignalMapper* cardSelectionMapper;
    QSignalMapper* cardPlantMapper;
    QPushButton* startButton;
    QLabel* background;
    QLabel* up;
    QLabel* down;
    QLabel* zombie[START_ZOMBIE_COUNT];
    int p[START_ZOMBIE_COUNT];
    int q[START_ZOMBIE_COUNT];

    int plantLabel;
    int enemyLabel;
    int sunshineLabel;
    int curSunshine;
    QLabel* showSunshineNum;
    QLabel* showSunshine;
    QPixmap picSunshine;

    QLabel* mousePic;
    QLabel* mouseShadow;
    int mouseLabel;

    int timerID;

private:
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent *event);
    QString getSplitColor(double per);
    void gamePreparation();
    void playStartAnimation();

private slots:
    void slotClickSunshine(int);
    void slotCardSelectAnimation();
    void slotBacktoSceneAnimation();
    void slotSceneLeftAnimation();
    void slotStart();
    void slotMoveCard(int);
    void slotClickStart();
    void slotPlant(int);

private:
    Ui::QGameDayInterface *ui;
};

#endif // QGAMEDAYINTERFACE_H
