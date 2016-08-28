#include "paireliminate.h"
#include "ui_paireliminate.h"

PairEliminate::PairEliminate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PairEliminate)
{
    ui->setupUi(this);

    for (int i = 0; i < TEMPLATE_COUNT; ++i)
    {
        std::string fileName = "Resources/paireliminate/maps/" + QString::number(i).toStdString() + ".txt";
        std::ifstream boardTemplate(fileName);
        for (int j = 0; j < PAIR_HEIGHT_COUNT; ++j)
        {
            std::string boardLine;
            boardTemplate >> boardLine;
            for (int k = 0; k < PAIR_WIDTH_COUNT; ++k)
            {
                char ch = boardLine[k];
                templateInts[i][j][k] = ch - 48;
            }
        }
    }

    for (int i = 0; i < CARD_COUNT; ++i)
    {
        QString fileName = "Resources/paireliminate/cards/" + QString::number(i) + ".gif";
        cardPics[i] = new QPixmap(fileName);
    }

    mp = new QSignalMapper(this);
    for (int i = 0; i < PAIR_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < PAIR_WIDTH_COUNT; ++j)
        {
            templateButtons[i][j] = new QPushButton(this);
            templateButtons[i][j]->setEnabled(false);
            templateButtons[i][j]->setGeometry(PAIR_START_X + PAIR_WIDTH * j, PAIR_START_Y + PAIR_HEIGHT * i, PAIR_WIDTH, PAIR_HEIGHT);
            templateButtons[i][j]->setIcon(*cardPics[0]);
            templateButtons[i][j]->setIconSize(QSize(PAIR_WIDTH, PAIR_HEIGHT));

            gameButtons[i][j] = new QPushButton(this);
            gameButtons[i][j]->setEnabled(true);
            gameButtons[i][j]->setGeometry(PAIR_START_X + PAIR_WIDTH * j, PAIR_START_Y + PAIR_HEIGHT * i, PAIR_WIDTH, PAIR_HEIGHT);
            gameButtons[i][j]->setIconSize(QSize(PAIR_WIDTH, PAIR_HEIGHT));
            QObject::connect(gameButtons[i][j], SIGNAL(clicked(bool)), mp, SLOT(map()));
            mp->setMapping(gameButtons[i][j], i * PAIR_WIDTH_COUNT + j);
        }
    }

    helpMsgbox = new QMessageBox(this);
    helpMsgbox->setText("将所有的方块成对消除后即可获得胜利。\n游戏时间限制为50秒，\n消除一对方块奖励3秒，\n使用一次提示扣除6秒，\n使用一次重排扣除剩余时间的1/3，\n最少扣除5秒。");
    helpMsgbox->addButton(QMessageBox::Ok);
    helpMsgbox->setIcon(QMessageBox::Information);

    succMsgbox = new QMessageBox(this);
    succMsgbox->addButton(QMessageBox::Ok);
    succMsgbox->setIcon(QMessageBox::Information);

    failMsgbox = new QMessageBox(this);
    failMsgbox->setText("\n您没有完成植物连连看。\n请再接再厉。");
    failMsgbox->addButton(QMessageBox::Ok);
    failMsgbox->setIcon(QMessageBox::Warning);

    gamePreparation();
    makeConnections();
    /*buttonPairs = new QPushButton**[PAIR_WIDTH_COUNT];
    for (int i = 0; i < PAIR_WIDTH_COUNT; ++i)
    {
        buttonPairs[i] = new QPushButton*[PAIR_HEIGHT_COUNT];
        for (int j = 0; j < PAIR_HEIGHT_COUNT; ++j)
        {
            buttonPairs[i][j] = new QPushButton(this);
            buttonPairs[i][j]->setText(QString::number(rand() % 10));
            buttonPairs[i][j]->setGeometry(PAIR_START_X + PAIR_WIDTH * i, PAIR_START_Y + PAIR_HEIGHT * j, PAIR_WIDTH, PAIR_HEIGHT);
            if (!((i + j) & 1)) buttonPairs[i][j]->setStyleSheet("QPushButton{""border:3px solid orange;}");
        }
    }*/

    ui->timeDisplay->setMaximum(MAX_TIME_DISPLAY);
    ui->timeDisplay->setEnabled(false);
}

PairEliminate::~PairEliminate()
{
    delete ui;
}

void PairEliminate::paintEvent(QPaintEvent* event)
{
    QPainter* painter = new QPainter(this);
    if (ui->label_2->isVisible())
    {
        double length = 300.0 * timeProgressing / MAX_TIME_DISPLAY;
        double split = 1.0 * timeProgressing / MAX_TIME_DISPLAY;
        QLinearGradient* linearGrad = new QLinearGradient(80, 565, length, 20);
        QString color = getSplitColor();
        linearGrad->setColorAt(0, "#ff0000");
        linearGrad->setColorAt(split, color);
        linearGrad->setStart(80, 565);
        linearGrad->setFinalStop(80 + length, 585);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(*linearGrad));
        painter->drawRect(80, 565, length, 20);

        painter->setBrush(QBrush("#dddddd"));
        painter->drawRect(80 + length, 565, 300 - length, 20);

        painter->setPen(QPen(Qt::black, 2));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(80, 565, 300, 20);
    }
    delete painter;
}

void PairEliminate::timerEvent(QTimerEvent *event)
{
    ++intervalCount;
    --timeProgressing;
    if (timeProgressing == 0)
    {
        failMsgbox->show();
        if (failMsgbox->exec() == QMessageBox::Ok)
        {
            gamePreparation();
        }
    }
    ui->timeDisplay->setValue(timeProgressing);
    this->update();
}

void PairEliminate::showTemplate()
{
    for (int i = 0; i < PAIR_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < PAIR_WIDTH_COUNT; ++j)
        {
            if (templateInts[curTemplate][i][j] == 1)
            {
                templateButtons[i][j]->show();
            }
            else
            {
                templateButtons[i][j]->hide();
            }
        }
    }
}

void PairEliminate::hideTemplate()
{
    for (int i = 0; i < PAIR_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < PAIR_WIDTH_COUNT; ++j)
        {
            templateButtons[i][j]->hide();
        }
    }
}

void PairEliminate::showGame()
{
    for (int i = 0; i < PAIR_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < PAIR_WIDTH_COUNT; ++j)
        {
            if (templateInts[curTemplate][i][j] == 1)
            {
                gameButtons[i][j]->show();
            }
            else
            {
                gameButtons[i][j]->hide();
            }
        }
    }
}

void PairEliminate::hideGame()
{
    for (int i = 0; i < PAIR_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < PAIR_WIDTH_COUNT; ++j)
        {
            gameButtons[i][j]->hide();
        }
    }
}

void PairEliminate::makeConnections()
{
    QObject::connect(ui->buttonStyleLeft, SIGNAL(clicked(bool)), this, SLOT(templateDec()));
    QObject::connect(ui->buttonStyleRight, SIGNAL(clicked(bool)), this, SLOT(templateInc()));
    QObject::connect(ui->timeDisplay, SIGNAL(valueChanged(int)), this, SLOT(timeDec()));
    QObject::connect(ui->buttonStart, SIGNAL(clicked(bool)), this, SLOT(gameStart()));
    QObject::connect(ui->buttonRestart, SIGNAL(clicked(bool)), this, SLOT(gamePreparation()));
    QObject::connect(ui->buttonHelp, SIGNAL(clicked(bool)), helpMsgbox, SLOT(show()));
    QObject::connect(ui->buttonExit, SIGNAL(clicked(bool)), qApp, SLOT(quit()));
    QObject::connect(mp, SIGNAL(mapped(int)), this, SLOT(cardPick(int)));
}

QString PairEliminate::getSplitColor()
{
    int per = static_cast<int>(255.0 * timeProgressing / MAX_TIME_DISPLAY);
    QString p = QString::number(255 - per, 16);
    QString q = QString::number(per, 16);
    if (p.size() == 1) p = "0" + p;
    if (q.size() == 1) q = "0" + q;
    return "#" + p + q + "00";
}

void PairEliminate::baseShuffle()
{

}

void PairEliminate::gameShuffle()
{
    while (true)
    {
        baseShuffle();
        if (findHint()) break;
    }
    ui->labelRed->hide();
}

bool PairEliminate::findHint()
{

}

void PairEliminate::eliminateHint()
{
    checkPath(hint1Pos, hint2Pos);
    eliminatePair(hint1, hint2);
}

void PairEliminate::eliminatePair(QPushButton *x, QPushButton *y)
{
    x->hide();
    y->hide();
    selectCard = nullptr;
    cardCount -= 2;
    if (cardCount == 0)
    {
        this->killTimer(myTimerId);
        succMsgbox->setText("\n您顺利完成了植物连连看。\n剩余时间" + QString::number(timeProgressing * TIME_ELAPSE / 1000) + "秒。");
        succMsgbox->show();
        if (succMsgbox->exec() == QMessageBox::Ok)
        {
            gamePreparation();
        }
    }
    else
    {
        if (findHint())
        {
            ui->labelRed->hide();

        }
        else
        {
            ui->labelRed->show();
        }
    }
}

bool PairEliminate::checkPath(Pos s, Pos t)
{

}

void PairEliminate::gamePreparation()
{
    ui->label_2->hide();
    ui->timeDisplay->hide();
    ui->buttonHint->hide();
    ui->buttonShuffle->hide();
    ui->buttonStyleLeft->show();
    ui->buttonStyleRight->show();
    ui->buttonStart->setEnabled(true);
    ui->buttonRestart->setEnabled(false);
    ui->labelRed->hide();

    selectCard = nullptr;
    selectPos.clear();

    curTemplate = 0;
    showTemplate();
    hideGame();
    this->update();

    this->killTimer(myTimerId);
}

void PairEliminate::gameStart()
{
    timeProgressing = MAX_TIME_DISPLAY;
    ui->label_2->show();
    ui->timeDisplay->setValue(timeProgressing);
    ui->buttonHint->show();
    ui->buttonShuffle->show();
    ui->buttonStyleLeft->hide();
    ui->buttonStyleRight->hide();
    ui->buttonStart->setEnabled(false);
    ui->buttonRestart->setEnabled(true);

    cardCount = -1;
    for (int i = 0; i < PAIR_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < PAIR_WIDTH_COUNT; ++j)
        {
            if (templateInts[curTemplate][i][j])
            {
                ++cardCount;
            }
        }
    }
    for (int i = 0; i < cardCount; i += 2)
    {
        int dummy = rand() % CARD_COUNT;
        randomInts[i] = dummy;
        randomInts[i + 1] = dummy;
    }
    std::random_shuffle(randomInts, randomInts + cardCount);
    int curCount = -1;
    for (int i = 0; i < PAIR_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < PAIR_WIDTH_COUNT; ++j)
        {
            if (templateInts[curTemplate][i][j])
            {
                ++curCount;
                gameButtons[i][j]->setIcon(*cardPics[randomInts[curCount]]);
                gameButtons[i][j]->setIconSize(QSize(PAIR_WIDTH, PAIR_HEIGHT));
                gameButtons[i][j]->setStyleSheet("QPushButton {background-color: black; color: white; border-radius: 10px; border: 2px groove gray; border-style: outset;}"
                                                 "QPushButton: hover {background-color: white; color: black;}"
                                                 "QPushButton: pressed {background-color: white; border-style: inset;}"
                                                );
                gameInts[i][j] = randomInts[curCount];
            }
        }
    }
    ++cardCount;
    hideTemplate();
    showGame();
    this->update();

    myTimerId = this->startTimer(TIME_ELAPSE);
    intervalCount = 0;

    hint1 = nullptr;
    hint2 = nullptr;
    hint1Pos.clear();
    hint2Pos.clear();
    paths.clear();
    eliminateTime.clear();
    pathHead = 0;
    pathTail = -1;
    if (findHint())
    {
        ui->labelRed->hide();
    }
    else
    {
        ui->labelRed->show();
    }
}

void PairEliminate::templateInc()
{
    ++curTemplate;
    if (curTemplate == TEMPLATE_COUNT) curTemplate = 0;
    this->showTemplate();
}

void PairEliminate::templateDec()
{
    --curTemplate;
    if (curTemplate == -1) curTemplate = TEMPLATE_COUNT - 1;
    this->showTemplate();
}

void PairEliminate::timeDec()
{
    timeProgressing = ui->timeDisplay->value();
}

void PairEliminate::cardPick(int p0)
{
    int xx = p0 / PAIR_WIDTH_COUNT;
    int yy = p0 % PAIR_WIDTH_COUNT;
    if (selectCard == nullptr)
    {
        selectCard = gameButtons[xx][yy];
        selectPos.modify(xx, yy);
        selectCard->setStyleSheet("QPushButton {background-color: black; color: white; border-radius: 10px; border: 4px orange; border-style: outset;}"
                                  "QPushButton: hover {background-color: white; color: black;}"
                                  "QPushButton: pressed {background-color: white; border-style: inset;}"
                                 );
    }
    else
    {
        if (gameInts[selectPos.x][selectPos.y] == gameInts[xx][yy])
        {
            bool check = checkPath(selectPos, Pos(xx, yy));
            if (check)
            {
                eliminatePair(selectCard, gameButtons[xx][yy]);
                if (selectCard->isHidden()) selectCard = nullptr;
            }
            else
            {
                selectCard->setStyleSheet("QPushButton {background-color: black; color: white; border-radius: 10px; border: 2px groove gray; border-style: outset;}"
                                          "QPushButton: hover {background-color: white; color: black;}"
                                          "QPushButton: pressed {background-color: white; border-style: inset;}"
                                         );
                selectCard = gameButtons[xx][yy];
                selectCard->setStyleSheet("QPushButton {background-color: black; color: white; border-radius: 10px; border: 4px orange; border-style: outset;}"
                                          "QPushButton: hover {background-color: white; color: black;}"
                                          "QPushButton: pressed {background-color: white; border-style: inset;}"
                                         );
            }
        }
        else
        {
            selectCard->setStyleSheet("QPushButton {background-color: black; color: white; border-radius: 10px; border: 2px groove gray; border-style: outset;}"
                                      "QPushButton: hover {background-color: white; color: black;}"
                                      "QPushButton: pressed {background-color: white; border-style: inset;}"
                                     );
            selectCard = gameButtons[xx][yy];
            selectCard->setStyleSheet("QPushButton {background-color: black; color: white; border-radius: 10px; border: 4px orange; border-style: outset;}"
                                      "QPushButton: hover {background-color: white; color: black;}"
                                      "QPushButton: pressed {background-color: white; border-style: inset;}"
                                     );
        }
    }
}

void PairEliminate::useHint()
{

}

void PairEliminate::useShuffle()
{

}
