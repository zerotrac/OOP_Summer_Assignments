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
#include <set>
#include <unordered_set>
#include "qplant.h"
#include "qzombie.h"
#include "qweapon.h"
#include "qsunshine.h"
#include "qcard.h"
#include "src_zombies/qcommonzombie.h"
#include "src_zombies/qconeheadzombie.h"
#include "src_zombies/qbucketheadzombie.h"
#include "src_zombies/qfootballzombie.h"
#include "src_zombies/qpolevaultingzombie.h"

#include "src_cards/qdoublepeacard.h"
#include "src_cards/qgatlingpeacard.h"
#include "src_cards/qpeashootercard.h"
#include "src_cards/qsnowpeacard.h"
#include "src_cards/qsunflowercard.h"
#include "src_cards/qtorchwoodcard.h"
#include "src_cards/qwallnutcard.h"
#include "src_cards/qtallnutcard.h"
#include "src_cards/qcherrybombcard.h"
#include "src_cards/qjalapenocard.h"
#include "src_cards/qpuffshroomcard.h"
#include "src_cards/qchompercard.h"
#include "src_cards/qscaredyshroomcard.h"
#include "src_cards/qpotatominecard.h"
#include "src_cards/qiceshroomcard.h"

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

    std::unordered_set<QWeapon*> plantWeapons;
    std::unordered_set<QWeapon*> enemyWeapons;
    std::vector<QPlant*> plants;
    std::vector<QZombie*> enemies;
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

    QLabel* shovelBack;
    QPushButton* shovel;
    QLabel* shovelPic;
    bool shovelInHand;

    int timerID;
    int giveSunshine;
    bool giveHP = false;


private:
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent *event);
    QString getSplitColor(double per);

public:
    void gamePreparation();

private:
    void playStartAnimation();

signals:
    void signalWidget(QString);

private slots:
    void slotClickSunshine(int);
    void slotCardSelectAnimation();
    void slotBacktoSceneAnimation();
    void slotSceneLeftAnimation();
    void slotStart();
    void slotMoveCard(int);
    void slotClickStart();
    void slotPlant(int);
    void slotShovel();

private:
    Ui::QGameDayInterface *ui;
};

#endif // QGAMEDAYINTERFACE_H
