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

    painter->setPen(QPen(Qt::white, 4));
    for (int i = pathHead; i <= pathTail; ++i)
    {
        for (int j = 0; j < paths[i].size() - 1; ++j)
        {
            painter->drawLine(PAIR_START_X + PAIR_WIDTH * (paths[i][j].y + 0.5), PAIR_START_Y + PAIR_HEIGHT * (paths[i][j].x + 0.5),
                              PAIR_START_X + PAIR_WIDTH * (paths[i][j + 1].y + 0.5), PAIR_START_Y + PAIR_HEIGHT * (paths[i][j + 1].x + 0.5));
        }
        painter->setBrush(Qt::white);
        painter->drawEllipse(QPoint(PAIR_START_X + PAIR_WIDTH * (paths[i][0].y + 0.5), PAIR_START_Y + PAIR_HEIGHT * (paths[i][0].x + 0.5)), 3, 3);
        int d = paths[i].size() - 1;
        painter->drawEllipse(QPoint(PAIR_START_X + PAIR_WIDTH * (paths[i][d].y + 0.5), PAIR_START_Y + PAIR_HEIGHT * (paths[i][d].x + 0.5)), 3, 3);
    }
    delete painter;
}

void PairEliminate::timerEvent(QTimerEvent *event)
{
    ++intervalCount;
    --timeProgressing;
    if (timeProgressing <= 0)
    {
        failMsgbox->show();
        if (failMsgbox->exec() == QMessageBox::Ok)
        {
            gamePreparation();
        }
    }
    // ui->timeDisplay->setValue(timeProgressing);

    //std::cout << "tevent = " << pathHead << " " << pathTail << std::endl;
    while (pathHead <= pathTail && intervalCount - eliminateTime[pathHead] >= LINE_TIME)
    {
        ++pathHead;
    }
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
    QObject::connect(ui->buttonHint, SIGNAL(clicked(bool)), this, SLOT(useHint()));
    QObject::connect(ui->buttonShuffle, SIGNAL(clicked(bool)), this, SLOT(useShuffle()));
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
    int dummy = -1;
    for (int i = 0; i < PAIR_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < PAIR_WIDTH_COUNT; ++j)
        {
            if (gameButtons[i][j]->isVisible())
            {
                ++dummy;
                randomInts[dummy] = gameInts[i][j];
            }
        }
    }
    std::random_shuffle(randomInts, randomInts + dummy + 1);
    for (int i = 0; i < PAIR_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < PAIR_WIDTH_COUNT; ++j)
        {
            if (gameButtons[i][j]->isVisible())
            {
                gameButtons[i][j]->setIcon(*cardPics[randomInts[dummy]]);
                gameInts[i][j] = randomInts[dummy];
                --dummy;
            }
        }
    }
}

void PairEliminate::gameShuffle()
{
    while (true)
    {
        baseShuffle();
        existSolution = findHint();
        if (existSolution) break;
    }
    ui->labelRed->hide();
}

bool PairEliminate::findHint()
{
    std::vector<Pos> queue;
    std::vector<int> level;
    int head = 0;
    int tail = -1;
    bool success = false;

    for (int i = 0; i < PAIR_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < PAIR_WIDTH_COUNT; ++j)
        {
            if (gameButtons[i][j]->isVisible())
            {
                queue.clear();
                level.clear();
                std::memset(used, false, sizeof(used));
                head = 0;
                tail = 0;
                queue.push_back(Pos(i, j));
                level.push_back(0);
                used[i + 1][j + 1] = true;
            }
            else
            {
                continue;
            }
            while (head <= tail)
            {
                Pos curPos = queue[head];
                int curLevel = level[head++];
                int xx = curPos.x;
                int yy = curPos.y;

                // U
                for (int k = 1;; ++k)
                {
                    if (xx - k < -1) break;
                    if (xx - k > -1 && xx - k < PAIR_HEIGHT_COUNT && yy > -1 && yy < PAIR_WIDTH_COUNT && gameButtons[xx - k][yy]->isVisible())
                    {
                        if (!(xx - k == i && yy == j) && gameInts[i][j] == gameInts[xx - k][yy])
                        {
                            success = true;
                            hint1 = gameButtons[i][j];
                            hint2 = gameButtons[xx - k][yy];
                            hint1Pos = Pos(i, j);
                            hint2Pos = Pos(xx - k, yy);
                        }
                        break;
                    }
                    else if (curLevel < 2 && !used[xx - k + 1][yy + 1])
                    {
                        ++tail;
                        queue.push_back(Pos(xx - k, yy));
                        level.push_back(curLevel + 1);
                        used[xx - k + 1][yy + 1] = true;
                    }
                }
                if (success) break;

                // D
                for (int k = 1;; ++k)
                {
                    if (xx + k > PAIR_HEIGHT_COUNT) break;
                    if (xx + k > -1 && xx + k < PAIR_HEIGHT_COUNT && yy > -1 && yy < PAIR_WIDTH_COUNT && gameButtons[xx + k][yy]->isVisible())
                    {
                        if (!(xx + k == i && yy == j) && gameInts[i][j] == gameInts[xx + k][yy])
                        {
                            success = true;
                            hint1 = gameButtons[i][j];
                            hint2 = gameButtons[xx + k][yy];
                            hint1Pos = Pos(i, j);
                            hint2Pos = Pos(xx + k, yy);
                        }
                        break;
                    }
                    else if (curLevel < 2 && !used[xx + k + 1][yy + 1])
                    {
                        ++tail;
                        queue.push_back(Pos(xx + k, yy));
                        level.push_back(curLevel + 1);
                        used[xx + k + 1][yy + 1] = true;
                    }
                }
                if (success) break;

                // L
                for (int k = 1;; ++k)
                {
                    if (yy - k < -1) break;
                    if (xx > -1 && xx < PAIR_HEIGHT_COUNT && yy - k > -1 && yy - k < PAIR_WIDTH_COUNT && gameButtons[xx][yy - k]->isVisible())
                    {
                        if (!(xx == i && yy - k == j) && gameInts[i][j] == gameInts[xx][yy - k])
                        {
                            success = true;
                            hint1 = gameButtons[i][j];
                            hint2 = gameButtons[xx][yy - k];
                            hint1Pos = Pos(i, j);
                            hint2Pos = Pos(xx, yy - k);
                        }
                        break;
                    }
                    else if (curLevel < 2 && !used[xx + 1][yy - k + 1])
                    {
                        ++tail;
                        queue.push_back(Pos(xx, yy - k));
                        level.push_back(curLevel + 1);
                        used[xx + 1][yy - k + 1] = true;
                    }
                }
                if (success) break;

                // R
                for (int k = 1;; ++k)
                {
                    if (yy + k > PAIR_WIDTH_COUNT) break;
                    if (xx > -1 && xx < PAIR_HEIGHT_COUNT && yy + k > -1 && yy + k < PAIR_WIDTH_COUNT && gameButtons[xx][yy + k]->isVisible())
                    {
                        if (!(xx == i && yy + k == j) && gameInts[i][j] == gameInts[xx][yy + k])
                        {
                            success = true;
                            hint1 = gameButtons[i][j];
                            hint2 = gameButtons[xx][yy + k];
                            hint1Pos = Pos(i, j);
                            hint2Pos = Pos(xx, yy + k);
                        }
                        break;
                    }
                    else if (curLevel < 2 && !used[xx + 1][yy + k + 1])
                    {
                        ++tail;
                        queue.push_back(Pos(xx, yy + k));
                        level.push_back(curLevel + 1);
                        used[xx + 1][yy + k + 1] = true;
                    }
                }
                if (success) break;
            }
            if (success) break;
        }
        if (success) break;
    }

    queue.clear();
    level.clear();
    return success;
}

void PairEliminate::eliminateHint()
{
    checkPath(hint1Pos, hint2Pos);
    eliminatePair(hint1, hint2, hint1Pos, hint2Pos);
}

void PairEliminate::eliminatePair(QPushButton*& x, QPushButton*& y, Pos xPos, Pos yPos)
{
    std::cout << "good" << std::endl;
    x->hide();
    y->hide();
    gameInts[xPos.x][xPos.y] = -1;
    gameInts[yPos.x][yPos.y] = -1;
    selectCard = nullptr;
    selectPos.clear();
    cardCount -= 2;
    timeProgressing += ELIMINATE_PRIZE;
    if (timeProgressing > MAX_TIME_DISPLAY) timeProgressing = MAX_TIME_DISPLAY;
    std::cout << "good2" << std::endl;
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
        std::cout << "good3" << std::endl;
        existSolution = findHint();
        if (existSolution)
        {
            ui->labelRed->hide();

        }
        else
        {
            ui->labelRed->show();
        }
        std::cout << "good4" << std::endl;
        std::cout << "ht = " << pathHead << " " << pathTail << std::endl;
    }
}

bool PairEliminate::checkPath(Pos s, Pos t)
{
    std::vector<Pos> queue;
    std::vector<int> level;
    std::vector<int> prev;
    std::memset(used, false, sizeof(used));
    int head = 0;
    int tail = 0;
    bool success = false;

    queue.push_back(s);
    level.push_back(0);
    prev.push_back(-1);
    used[s.x + 1][s.y + 1] = true;

    while (head <= tail)
    {
        Pos curPos = queue[head];
        int curLevel = level[head++];
        int xx = curPos.x;
        int yy = curPos.y;

        // U
        for (int k = 1;; ++k)
        {
            if (xx - k < -1) break;
            if (xx - k > -1 && xx - k < PAIR_HEIGHT_COUNT && yy > -1 && yy < PAIR_WIDTH_COUNT && gameButtons[xx - k][yy]->isVisible())
            {
                if (xx - k == t.x && yy == t.y)
                {
                    success = true;
                    std::vector<Pos> path;
                    path.push_back(Pos(t.x, t.y));
                    int where = head - 1;
                    while (where != -1)
                    {
                        path.push_back(queue[where]);
                        where = prev[where];
                    }
                    ++pathTail;
                    paths.push_back(path);
                    eliminateTime.push_back(intervalCount);
                }
                break;
            }
            else if (curLevel < 2 && !used[xx - k + 1][yy + 1])
            {
                ++tail;
                queue.push_back(Pos(xx - k, yy));
                level.push_back(curLevel + 1);
                prev.push_back(head - 1);
                used[xx - k + 1][yy + 1] = true;
            }
        }
        if (success) break;

        // D
        for (int k = 1;; ++k)
        {
            if (xx + k > PAIR_HEIGHT_COUNT) break;
            if (xx + k > -1 && xx + k < PAIR_HEIGHT_COUNT && yy > -1 && yy < PAIR_WIDTH_COUNT && gameButtons[xx + k][yy]->isVisible())
            {
                if (xx + k == t.x && yy == t.y)
                {
                    success = true;
                    std::vector<Pos> path;
                    path.push_back(Pos(t.x, t.y));
                    int where = head - 1;
                    while (where != -1)
                    {
                        path.push_back(queue[where]);
                        where = prev[where];
                    }
                    ++pathTail;
                    paths.push_back(path);
                    eliminateTime.push_back(intervalCount);
                }
                break;
            }
            else if (curLevel < 2 && !used[xx + k + 1][yy + 1])
            {
                ++tail;
                queue.push_back(Pos(xx + k, yy));
                level.push_back(curLevel + 1);
                prev.push_back(head - 1);
                used[xx + k + 1][yy + 1] = true;
            }
        }
        if (success) break;

        // L
        for (int k = 1;; ++k)
        {
            if (yy - k < -1) break;
            if (xx > -1 && xx < PAIR_HEIGHT_COUNT && yy - k > -1 && yy - k < PAIR_WIDTH_COUNT && gameButtons[xx][yy - k]->isVisible())
            {
                if (xx == t.x && yy - k == t.y)
                {
                    success = true;
                    std::vector<Pos> path;
                    path.push_back(Pos(t.x, t.y));
                    int where = head - 1;
                    while (where != -1)
                    {
                        path.push_back(queue[where]);
                        where = prev[where];
                    }
                    ++pathTail;
                    paths.push_back(path);
                    eliminateTime.push_back(intervalCount);
                }
                break;
            }
            else if (curLevel < 2 && !used[xx + 1][yy - k + 1])
            {
                ++tail;
                queue.push_back(Pos(xx, yy - k));
                level.push_back(curLevel + 1);
                prev.push_back(head - 1);
                used[xx + 1][yy - k + 1] = true;
            }
        }
        if (success) break;

        // R
        for (int k = 1;; ++k)
        {
            if (yy + k > PAIR_WIDTH_COUNT) break;
            if (xx > -1 && xx < PAIR_HEIGHT_COUNT && yy + k > -1 && yy + k < PAIR_WIDTH_COUNT && gameButtons[xx][yy + k]->isVisible())
            {
                if (xx == t.x && yy + k == t.y)
                {
                    success = true;
                    std::vector<Pos> path;
                    path.push_back(Pos(t.x, t.y));
                    int where = head - 1;
                    while (where != -1)
                    {
                        path.push_back(queue[where]);
                        where = prev[where];
                    }
                    ++pathTail;
                    paths.push_back(path);
                    eliminateTime.push_back(intervalCount);
                }
                break;
            }
            else if (curLevel < 2 && !used[xx + 1][yy + k + 1])
            {
                ++tail;
                queue.push_back(Pos(xx, yy + k));
                level.push_back(curLevel + 1);
                prev.push_back(head - 1);
                used[xx + 1][yy + k + 1] = true;
            }
        }
        if (success) break;
    }

    queue.clear();
    level.clear();
    prev.clear();
    std::cout << "success = " << success << std::endl;
    return success;
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
    paths.clear();
    eliminateTime.clear();
    pathHead = 0;
    pathTail = -1;

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

    std::random_shuffle(randomInts, randomInts + cardCount + 1);
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
                                                 "QPushButton:hover {background-color: white; color: black;}"
                                                 "QPushButton:pressed {background-color: white; border-style: inset;}"
                                                );
                gameInts[i][j] = randomInts[curCount];
            }
            else
            {
                gameInts[i][j] = -1;
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
    existSolution = findHint();

    if (existSolution)
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
    if (xx == selectPos.x && yy == selectPos.y)
    {
        return;
    }

    if (selectCard == nullptr)
    {
        selectCard = gameButtons[xx][yy];
        selectPos.modify(xx, yy);
        selectCard->setStyleSheet("QPushButton {background-color: black; color: white; border-radius: 10px; border: 4px orange; border-style: outset;}"
                                  "QPushButton:hover {background-color: white; color: black;}"
                                  "QPushButton:pressed {background-color: white; border-style: inset;}"
                                 );
    }
    else
    {
        if (gameInts[selectPos.x][selectPos.y] == gameInts[xx][yy])
        {
            bool check = checkPath(selectPos, Pos(xx, yy));
            if (check)
            {
                eliminatePair(selectCard, gameButtons[xx][yy], selectPos, Pos(xx, yy));
                std::cout << "good4.5" << std::endl;
            }
            else
            {
                selectCard->setStyleSheet("QPushButton {background-color: black; color: white; border-radius: 10px; border: 2px groove gray; border-style: outset;}"
                                          "QPushButton:hover {background-color: white; color: black;}"
                                          "QPushButton:pressed {background-color: white; border-style: inset;}"
                                         );
                selectCard = gameButtons[xx][yy];
                selectPos = Pos(xx, yy);
                selectCard->setStyleSheet("QPushButton {background-color: black; color: white; border-radius: 10px; border: 4px orange; border-style: outset;}"
                                          "QPushButton:hover {background-color: white; color: black;}"
                                          "QPushButton:pressed {background-color: white; border-style: inset;}"
                                         );
            }
        }
        else
        {
            selectCard->setStyleSheet("QPushButton {background-color: black; color: white; border-radius: 10px; border: 2px groove gray; border-style: outset;}"
                                      "QPushButton:hover {background-color: white; color: black;}"
                                      "QPushButton:pressed {background-color: white; border-style: inset;}"
                                     );
            selectCard = gameButtons[xx][yy];
            selectPos = Pos(xx, yy);
            selectCard->setStyleSheet("QPushButton {background-color: black; color: white; border-radius: 10px; border: 4px orange; border-style: outset;}"
                                      "QPushButton:hover {background-color: white; color: black;}"
                                      "QPushButton:pressed {background-color: white; border-style: inset;}"
                                     );
        }
    }
    std::cout << "good5" << std::endl;
}

void PairEliminate::useHint()
{
    if (existSolution)
    {
        eliminateHint();
        timeProgressing -= HINT_COST;
        selectCard = nullptr;
        selectPos.clear();
    }
}

void PairEliminate::useShuffle()
{
    gameShuffle();
    int decTime = timeProgressing * SHUFFLE_COST;
    decTime = std::max(decTime, 5 * 1000 / TIME_ELAPSE);
    timeProgressing -= decTime;
    selectCard = nullptr;
    selectPos.clear();
}
