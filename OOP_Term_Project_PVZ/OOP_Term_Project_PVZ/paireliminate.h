#ifndef PAIRELIMINATE_H
#define PAIRELIMINATE_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QMessageBox>
#include <QSignalMapper>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include "const.h"

namespace Ui {
class PairEliminate;
}

class PairEliminate : public QWidget
{
    Q_OBJECT

public:
    explicit PairEliminate(QWidget *parent = 0);
    ~PairEliminate();

private:
    static const int PAIR_WIDTH_COUNT = 19;
    static const int PAIR_HEIGHT_COUNT = 11;
    static const int PAIR_WIDTH = 30;
    static const int PAIR_HEIGHT = PAIR_WIDTH * 1.2;
    static const int PAIR_START_X = 165;
    static const int PAIR_START_Y = 100;
    static const int TEMPLATE_COUNT = 10;
    static const int CARD_COUNT = 24;

    static const int MAX_TIME = 60; // 游戏时间
    static const int MAX_TIME_DISPLAY = 1000 / TIME_ELAPSE * MAX_TIME; // 进度条长度
    static const int LINE_TIME = 0.5 * 1000 / TIME_ELAPSE;

    static const int ELIMINATE_PRIZE = 1 * 1000 / TIME_ELAPSE;
    static const int HINT_COST = 5 * 1000 / TIME_ELAPSE;
    static constexpr double SHUFFLE_COST = 1.0 / 3;

private:
    struct Pos
    {
        int x, y;
        Pos(): x(-1), y(-1) {}
        Pos(int _x): x(_x / PAIR_WIDTH_COUNT), y(_x % PAIR_WIDTH_COUNT) {}
        Pos(int _x, int _y): x(_x), y(_y) {}
        void clear() {modify(-1, -1);}
        void modify(int _x, int _y) {x = _x, y = _y;}
    };

private:
    QMessageBox* helpMsgbox;
    QMessageBox* succMsgbox;
    QMessageBox* failMsgbox;

    int templateInts[TEMPLATE_COUNT][PAIR_HEIGHT_COUNT][PAIR_WIDTH_COUNT];
    QPushButton* templateButtons[PAIR_HEIGHT_COUNT][PAIR_WIDTH_COUNT];
    int randomInts[PAIR_HEIGHT_COUNT * PAIR_WIDTH_COUNT];
    int gameInts[PAIR_HEIGHT_COUNT][PAIR_WIDTH_COUNT];
    QPushButton* gameButtons[PAIR_HEIGHT_COUNT][PAIR_WIDTH_COUNT];
    QSignalMapper* mp;
    QPixmap* cardPics[CARD_COUNT];
    QPushButton* selectCard;
    Pos selectPos;

    bool existSolution;
    QPushButton* hint1;
    Pos hint1Pos;
    QPushButton* hint2;
    Pos hint2Pos;

    std::vector<std::vector<Pos>> paths;
    std::vector<int> eliminateTime;
    bool used[PAIR_HEIGHT_COUNT + 2][PAIR_WIDTH_COUNT + 2];
    int pathHead = 0;
    int pathTail = -1;

    int curTemplate;
    int timeProgressing;
    int cardCount;
    int myTimerId;
    int intervalCount;

private:
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent* event);
    void showTemplate();
    void hideTemplate();
    void showGame();
    void hideGame();
    void makeConnections();
    QString getSplitColor();
    void baseShuffle();
    void gameShuffle();
    bool findHint();
    void eliminateHint();
    void eliminatePair(QPushButton*&, QPushButton*&, Pos xPos, Pos yPos);
    bool checkPath(Pos s, Pos t);

signals:
    void signalWidget(QString);

public slots:
    void gamePreparation();

private slots:
    void gameStart();
    void templateInc();
    void templateDec();
    //void timeInc();
    void timeDec();
    void cardPick(int p0);
    void useHint();
    void useShuffle();
    void slotQuit();

private:
    Ui::PairEliminate *ui;
};

#endif // PAIRELIMINATE_H
