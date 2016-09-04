#include "qgamedayinterface.h"
#include "ui_qgamedayinterface.h"
#include <iostream>

QGameDayInterface::QGameDayInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGameDayInterface)
{
    ui->setupUi(this);

    this->setFocusPolicy(Qt::StrongFocus);
    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap backgroundBig("Resources/interface/day_background.jpg");
    QPixmap backgroundSmall = backgroundBig.copy(120, 0, 900, 600);
    palette.setBrush(QPalette::Background, QBrush(backgroundSmall));
    this->setPalette(palette);

    background = new QLabel(this);
    QPixmap backPic("Resources/interface/day_background.jpg");
    background->setFixedSize(backPic.size());
    background->setPixmap(backPic);

    up = new QLabel(this);
    QPixmap upPic("Resources/interface/card_up.png");
    up->setFixedSize(upPic.size());
    up->setPixmap(upPic);

    down = new QLabel(this);
    QPixmap downPic0("Resources/interface/card_down.png");
    QPixmap downPic = downPic0.scaled(downPic0.size() * 0.93);
    down->setFixedSize(downPic.size());
    down->setPixmap(downPic);

    picSunshine.load("Resources/sunshine/sun.gif");
    picSunshine = picSunshine.scaled(picSunshine.width() * 0.75, picSunshine.height() * 0.75);
    showSunshine = new QLabel(this);
    showSunshine->setFixedSize(picSunshine.size());
    showSunshine->setGeometry(10, 6, 0, 0);
    showSunshine->setPixmap(picSunshine);
    showSunshineNum = new QLabel(this);
    showSunshineNum->setFixedSize(50, 20);

    sunshineMapper = nullptr;
    cardSelectionMapper = nullptr;
    cardPlantMapper = nullptr;

    startButton = new QPushButton(this);
    startButton->setFixedSize(QPixmap("Resources/interface/card_start.png").size());
    startButton->setStyleSheet("QPushButton {border-image: url(Resources/interface/card_start.png);}");
    startButton->setText("  游戏开始！");
    startButton->setCursor(Qt::PointingHandCursor);

    QPalette palForStartButton;
    palForStartButton.setColor(QPalette::ButtonText, Qt::white);
    startButton->setPalette(palForStartButton);
    QObject::connect(startButton, SIGNAL(clicked(bool)), this, SLOT(slotClickStart()));

    for (int i = 0; i < CARD_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < CARD_WIDTH_COUNT; ++j)
        {
            cards[i][j] = nullptr;
        }
    }
    cards[0][0] = new QSunflowerCard(0); cards[0][0]->setParent(this);
    cards[0][1] = new QPeashooterCard(1); cards[0][1]->setParent(this);
    cards[0][2] = new QSnowPeaCard(2); cards[0][2]->setParent(this);
    cards[0][3] = new QDoublePeaCard(3);cards[0][3]->setParent(this);
    cards[0][4] = new QGatlingPeaCard(4); cards[0][4]->setParent(this);
    cards[0][5] = new QWallnutCard(5); cards[0][5]->setParent(this);
    cards[0][6] = new QTorchwoodCard(6); cards[0][6]->setParent(this);
    cards[0][7] = new QTallnutCard(7); cards[0][7]->setParent(this);

    for (int i = 0; i < START_ZOMBIE_COUNT; ++i)
    {
        zombie[i] = new QLabel(this);
        QMovie* zombieMov = new QMovie("Resources/zombies/zombie/laugh.gif");
        zombieMov->start();
        zombie[i]->setFixedSize(zombieMov->currentPixmap().size());
        zombie[i]->setMovie(zombieMov);
    }

    mousePic = new QLabel(this);
    mousePic->hide();
    mouseShadow = new QLabel(this);
    mouseShadow->hide();

    gamePreparation();
    slotCardSelectAnimation();
    //playStartAnimation();

    /*for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            ++plantLabel;
            //qDebug() << "label =" << plantLabel;
            QPlant* plt;
            if (j == 0) plt = new QSunflower(plantLabel);
            else if (j == 1) plt = new QPeashooter(plantLabel);
            else if (j == 2) plt = new QDoublePea(plantLabel);
            else if (j == 3) plt = new QSnowPea(plantLabel);
            else if (j == 4) plt = new QGatlingPea(plantLabel);
            else if (j == 5) plt = new QTorchwood(plantLabel);
            else plt = new QWallnut(plantLabel);

            plt->setAxis(140 + j * 80, 170 + i * 95);
            plt->setParent(this);
            plantsID.insert(plantLabel);
            plants.push_back(plt);
        }
    }*/
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 7; j < 9; ++j)
        {
            ++enemyLabel;
            QPlant* plt;
            if (j == 7) plt = new QPeashooter(plantLabel);
            else plt = new QWallnut(plantLabel);
            plt->setAxis(140 + j * 80, 170 + i * 95);
            plt->setParent(this);
            enemiesID.insert(enemyLabel);
            enemies.push_back(plt);
        }
    }
}

QGameDayInterface::~QGameDayInterface()
{
    delete ui;
}

void QGameDayInterface::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (mouseShadow->isHidden()) return;

        QPoint p = this->mapFromGlobal(this->cursor().pos());
        bool ok = false;
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (p.x() >= 140 + j * 80 && p.x() <= 220 + j * 80 && p.y() >= 75 + i * 95 && p.y() <= 170 + i * 95)
                {
                    ++plantLabel;
                    QPlant* plt = cardsCanUse[mouseLabel]->getPlant(plantLabel);
                    qDebug() << "good generate!" << plt->width() << plt->height();
                    plt->setAxis(140 + j * 80, 170 + i * 95);
                    plt->setParent(this);
                    plt->show();
                    plantsID.insert(plantLabel);
                    plants.push_back(plt);
                    curSunshine -= cardsCanUse[mouseLabel]->sunshineCost;
                    ok = true;
                    break;
                }
                if (ok) break;
            }
        }

        mousePic->hide();
        mouseShadow->hide();
        mouseLabel = -1;
    }
    else if (event->button() == Qt::RightButton)
    {
        mousePic->hide();
        mouseShadow->hide();
        mouseLabel = -1;
    }
}

void QGameDayInterface::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    if (key == Qt::Key_A)
    {
        curSunshine += 100;
    }
    else if (key == Qt::Key_D)
    {
        curSunshine -= 100;
        if (curSunshine < 0) curSunshine = 0;
    }
}

void QGameDayInterface::paintEvent(QPaintEvent *event)
{
    QPainter* painter = new QPainter(this);
    for (int plantID: plantsID)
    {
        QPlant* plant = plants[plantID];
        double per = 1.0 * plant->getCurrentHP() / plant->getMaxHP();

        QString color = getSplitColor(per);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(color));
        QRectF rect2(plant->pos().x(), plant->pos().y() - 10, 1.0 * plant->width() * per, 10);
        painter->drawRect(rect2);

        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(Qt::NoBrush);
        QRectF rect1(plant->pos().x(), plant->pos().y() - 10, plant->width(), 10);
        painter->drawRect(rect1);
    }
    for (int enemyID: enemiesID)
    {
        QPlant* enemy = enemies[enemyID];
        double per = 1.0 * enemy->getCurrentHP() / enemy->getMaxHP();

        QString color = getSplitColor(per);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(color));
        QRectF rect2(enemy->pos().x(), enemy->pos().y() - 10, 1.0 * enemy->width() * per, 10);
        painter->drawRect(rect2);

        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(Qt::NoBrush);
        QRectF rect1(enemy->pos().x(), enemy->pos().y() - 10, enemy->width(), 10);
        painter->drawRect(rect1);
    }
    delete painter;
}

void QGameDayInterface::timerEvent(QTimerEvent *event)
{
    if (mouseLabel != -1)
    {
        QPoint p = this->mapFromGlobal(this->cursor().pos());
        mousePic->setGeometry(p.x() - mousePic->width() / 2, p.y() - mousePic->height() / 2, mousePic->width(), mousePic->height());
        bool ok = false;
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (p.x() >= 140 + j * 80 && p.x() <= 220 + j * 80 && p.y() >= 75 + i * 95 && p.y() <= 170 + i * 95)
                {
                    bool ok0 = true;
                    for (QPlant* plant: plants)
                    {
                        if (plant->pos().x() == 140 + j * 80 && plant->pos().y() + plant->height() == 170 + i * 95)
                        {
                            ok0 = false;
                            break;
                        }
                    }
                    if (ok0)
                    {
                        mouseShadow->show();
                        mouseShadow->setGeometry(140 + j * 80, 170 + i * 95 - mouseShadow->height(), mouseShadow->width(), mouseShadow->height());
                        ok = true;
                        break;
                    }
                }
                if (ok) break;
            }
        }
        if (!ok)
        {
            mouseShadow->hide();
        }
    }

    if (event->timerId() == timerID)
    {
        showSunshineNum->setText(QString::number(curSunshine));
        showSunshineNum->setGeometry(40 - showSunshineNum->text().length() * 4, 62, 0, 0);
        showSunshineNum->show();
        //showSunshineNum->raise();
        showSunshine->show();
        //showSunshine->raise();
        // 步骤：
        // 1. 武器与其它单位进行判定，僵尸销毁
        // 2. 武器移动，武器销毁
        // 3. 植物攻击判定
        // 4. 僵尸攻击判定，植物销毁
        for (QWeapon* weapon: weapons) // 处理武器
        {
            for (int plantID: plantsID) // 处理火炬树桩对武器的作用
            {
                QPlant* plant = plants[plantID];
                if (weapon->inRange(plant) && plant->canLitUp())
                {
                    weapon->setLit(plantID);
                }
            }
            for (int enemyID: enemiesID) // 处理武器对僵尸
            {
                QPlant* enemy = enemies[enemyID];
                if (!enemy->isDead() && !weapon->outofDuration() && weapon->inRange(enemy))
                {
                    //qDebug() << "weapon location =" << weapon->pos().x() << weapon->pos().y();
                    enemy->beAttacked(weapon->atk);
                    weapon->decBullet();
                }
            }
        }
        //qDebug() << "good1";
        for (auto iter = enemiesID.begin(); iter != enemiesID.end();) // 处理死亡的僵尸
        {
            if (enemies[*iter]->isDead())
            {
                delete enemies[*iter];
                enemiesID.erase(iter++);
            }
            else
            {
                ++iter;
            }
        }
        //qDebug() << "good2";
        for (QWeapon* weapon: weapons) // 处理武器移动
        {
            if (!weapon->outofDuration())
            {
                weapon->updateInfo();
                weapon->show();
            }
        }
        //qDebug() << "good3";
        for (auto iter = weapons.begin(); iter != weapons.end();) // 一次性武器判定
        {
            if ((*iter)->outofDuration())
            {
                delete (*iter);
                weapons.erase(iter++);
            }
            else
            {
                ++iter;
            }
        }
        //qDebug() << "good4";
        for (QSunshine* sunshine: sunshines) // 处理阳光
        {
            sunshine->updateInfo();
            sunshine->show();
        }
        //qDebug() << "good5";
        for (int plantID: plantsID) // 处理植物
        {
            QPlant* plant = plants[plantID];
            bool ok = false;
            for (int enemyID: enemiesID) // 植物攻击判定
            {
                QPlant* enemy = enemies[enemyID];
                ok |= plant->canAttack(enemy);
            }
            if (ok)
            {
                std::vector<QWeapon*> wps = plant->attack();
                for (QWeapon* wp: wps)
                {
                    wp->setAxis(plant->pos().x() + plant->width() / 2, plant->pos().y() + plant->height() / 2);
                    wp->setParent(this);
                    weapons.insert(wp);
                }
            }

            if (plant->canGenerateSunshine()) // 植物产生阳光判定
            {
                ++sunshineLabel;
                QSunshine* sunshine = plant->generateSunshine(sunshineLabel);
                sunshine->setGenerateID(plant->id);
                sunshine->setAxis(plant->pos().x() - plant->width() / 6.0, plant->pos().y() + plant->height() / 3.0 * 2.0);
                sunshine->setParent(this);
                sunshine->setDestination(plant->pos().x() - plant->width() / 6.0, plant->pos().y() + plant->height() / 3.0 * 2.0);
                sunshine->setSpeed(0, 0);
                sunshinesID.insert(sunshineLabel);
                sunshines.push_back(sunshine);

                QObject::connect(sunshine, SIGNAL(clicked(bool)), sunshineMapper, SLOT(map()));
                sunshineMapper->setMapping(sunshine, sunshineLabel);
            }

            plant->updateInfo();
        }
        for (auto iter = plantsID.begin(); iter != plantsID.end();) // 一次性植物判定
        {
            if (plants[*iter]->isDead())
            {
                delete plants[*iter];
                plantsID.erase(iter++);
            }
            else
            {
                ++iter;
            }
        }
        //qDebug() << "good6";
        for (int enemyID: enemiesID)
        {
            QPlant* enemy = enemies[enemyID];
            enemy->updateInfo();
        }

        for (QCard* card: cardsCanUse)
        {
            card->updateInfo(curSunshine);
        }
    }
    this->update();
}

QString QGameDayInterface::getSplitColor(double _per)
{
    int per = static_cast<int>(255.0 * _per);
    QString p = QString::number(255 - per, 16);
    QString q = QString::number(per, 16);
    if (p.size() == 1) p = "0" + p;
    if (q.size() == 1) q = "0" + q;
    return "#" + p + q + "00";
}

void QGameDayInterface::gamePreparation()
{
    plantsID.clear();
    enemiesID.clear();
    weapons.clear();
    for (QPlant* plant: plants)
    {
        if (plant != nullptr) delete plant;
    }
    for (QPlant* enemy: enemies)
    {
        if (enemy != nullptr) delete enemy;
    }
    for (QSunshine* sunshine: sunshines)
    {
        if (sunshine != nullptr) delete sunshine;
    }
    plants.clear();
    enemies.clear();
    sunshines.clear();

    plantLabel = -1;
    enemyLabel = -1;
    sunshineLabel = -1;
    curSunshine = 50;

    if (sunshineMapper != nullptr) delete sunshineMapper;
    sunshineMapper = new QSignalMapper(this);
    QObject::connect(sunshineMapper, SIGNAL(mapped(int)), this, SLOT(slotClickSunshine(int)));

    if (cardSelectionMapper != nullptr) delete cardSelectionMapper;
    cardSelectionMapper = new QSignalMapper(this);
    QObject::connect(cardSelectionMapper, SIGNAL(mapped(int)), this, SLOT(slotMoveCard(int)));
    for (int i = 0; i < CARD_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < CARD_WIDTH_COUNT; ++j)
        {
            if (cards[i][j] != nullptr)
            {
                cards[i][j]->initialize();
                QObject::connect(cards[i][j], SIGNAL(clicked(bool)), cardSelectionMapper, SLOT(map()));
                cardSelectionMapper->setMapping(cards[i][j], i * CARD_WIDTH_COUNT + j);
                cards[i][j]->hide();
            }
        }
    }
    cardsTop = -1;
    for (int i = 0; i < CARD_CAN_USE; ++i)
    {
        cardsCanUse[i] = nullptr;
    }

    background->hide();
    up->hide();
    down->hide();
    startButton->hide();
    showSunshineNum->hide();
    showSunshine->hide();

    for (int i = 0; i < START_ZOMBIE_COUNT; ++i)
    {
        zombie[i]->hide();
    }

    mouseLabel = -1;
}

void QGameDayInterface::playStartAnimation()
{
    QParallelAnimationGroup *startAni = new QParallelAnimationGroup(this);
    QPropertyAnimation *propAni;
    propAni = new QPropertyAnimation(background, "pos", this);
    propAni->setDuration(4000);
    propAni->setEasingCurve(QEasingCurve(QEasingCurve::InOutCubic));
    propAni->setKeyValueAt(0.0, QPoint(0, 0));
    propAni->setKeyValueAt(0.5, QPoint(0, 0));
    propAni->setKeyValueAt(1.0, QPoint(-500, 0));
    startAni->addAnimation(propAni);
    background->show();

    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    int thres = START_ZOMBIE_COUNT;
    while (1)
    {
        for (int i = 0; i < thres; ++i)
        {
            p[i] = qrand() % 250 + 500;
            q[i] = qrand() % 450;
        }
        bool flag = true;
        for (int i = 0; i < thres - 1; ++i)
        {
            for (int j = i + 1; j < thres; ++j)
            {
                if (std::abs(p[i] - p[j]) < 15 || std::abs(q[i] - q[j]) < 15)
                {
                    flag = false;
                    break;
                }
            }
            if (!flag) break;
        }
        if (flag) break;
    }
    for (int i = 0; i < thres - 1; ++i)
    {
        for (int j = i + 1; j < thres; ++j)
        {
            if (q[i] > q[j])
            {
                std::swap(p[i], p[j]);
                std::swap(q[i], q[j]);
            }
        }
    }

    for (int i = 0; i < thres; ++i)
    {
        propAni = new QPropertyAnimation(zombie[i], "pos", this);
        propAni->setDuration(4000);
        propAni->setEasingCurve(QEasingCurve(QEasingCurve::InOutCubic));
        propAni->setKeyValueAt(0.0, QPoint(p[i] + 500, q[i]));
        propAni->setKeyValueAt(0.5, QPoint(p[i] + 500, q[i]));
        propAni->setKeyValueAt(1.0, QPoint(p[i], q[i]));
        startAni->addAnimation(propAni);
        zombie[i]->show();
    }
    QAbstractAnimation* ani = startAni;
    ani->start(QAbstractAnimation::DeleteWhenStopped);
    QObject::connect(ani, SIGNAL(finished()), this, SLOT(slotCardSelectAnimation()));
}

void QGameDayInterface::slotCardSelectAnimation()
{
    QParallelAnimationGroup *selectAni = new QParallelAnimationGroup(this);
    QPropertyAnimation *propAni;

    propAni = new QPropertyAnimation(up, "pos", this);
    propAni->setDuration(1100);
    propAni->setEasingCurve(QEasingCurve(QEasingCurve::InOutCubic));
    propAni->setKeyValueAt(0.0, QPoint(0, -up->height()));
    propAni->setKeyValueAt(1.0 - 100.0 / 1100, QPoint(0, -up->height()));
    propAni->setKeyValueAt(1.0, QPoint(0, 0));
    selectAni->addAnimation(propAni);
    up->show();

    propAni = new QPropertyAnimation(down, "pos", this);
    propAni->setDuration(1100);
    propAni->setEasingCurve(QEasingCurve(QEasingCurve::InOutCubic));
    propAni->setKeyValueAt(0.0, QPoint(0, WINDOW_HEIGHT));
    propAni->setKeyValueAt(1.0 - 100.0 / 1100, QPoint(0, WINDOW_HEIGHT));
    propAni->setKeyValueAt(1.0, QPoint(0, WINDOW_HEIGHT - down->height()));
    selectAni->addAnimation(propAni);
    down->show();

    propAni = new QPropertyAnimation(startButton, "pos", this);
    propAni->setDuration(1100);
    propAni->setEasingCurve(QEasingCurve(QEasingCurve::InOutCubic));
    propAni->setKeyValueAt(0.0, QPoint(160, 550 + down->height()));
    propAni->setKeyValueAt(1.0 - 100.0 / 1100, QPoint(160, 550 + down->height()));
    propAni->setKeyValueAt(1.0, QPoint(160, 550));
    selectAni->addAnimation(propAni);
    startButton->show();

    for (int i = 0; i < CARD_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < CARD_WIDTH_COUNT; ++j)
        {
            if (cards[i][j] != nullptr)
            {
                propAni = new QPropertyAnimation(cards[i][j], "pos", this);
                propAni->setDuration(1100);
                propAni->setEasingCurve(QEasingCurve(QEasingCurve::InOutCubic));
                propAni->setKeyValueAt(0.0, QPoint(cards[i][j]->pos().x(), cards[i][j]->pos().y() + down->height()));
                propAni->setKeyValueAt(1.0 - 100.0 / 1100, QPoint(cards[i][j]->pos().x(), cards[i][j]->pos().y() + down->height()));
                propAni->setKeyValueAt(1.0, cards[i][j]->pos());
                selectAni->addAnimation(propAni);
                cards[i][j]->show();
            }
        }
    }
    QAbstractAnimation* ani = selectAni;
    ani->start(QAbstractAnimation::DeleteWhenStopped);
}

void QGameDayInterface::slotBacktoSceneAnimation()
{
    for (int i = 0; i < CARD_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < CARD_WIDTH_COUNT; ++j)
        {
            if (cards[i][j] != nullptr)
            {
                cards[i][j]->disconnect();
            }
        }
    }

    QParallelAnimationGroup *selectAni = new QParallelAnimationGroup(this);
    QPropertyAnimation *propAni;

    int duration = 500;
    propAni = new QPropertyAnimation(down, "pos", this);
    propAni->setDuration(duration);
    propAni->setEasingCurve(QEasingCurve(QEasingCurve::InOutCubic));
    propAni->setKeyValueAt(0.0, QPoint(0, WINDOW_HEIGHT - down->height()));
    propAni->setKeyValueAt(1.0, QPoint(0, WINDOW_HEIGHT));
    selectAni->addAnimation(propAni);

    propAni = new QPropertyAnimation(startButton, "pos", this);
    propAni->setDuration(duration);
    propAni->setEasingCurve(QEasingCurve(QEasingCurve::InOutCubic));
    propAni->setKeyValueAt(0.0, QPoint(160, 550));
    propAni->setKeyValueAt(1.0, QPoint(160, 550 + down->height()));
    selectAni->addAnimation(propAni);

    for (int i = 0; i < CARD_HEIGHT_COUNT; ++i)
    {
        for (int j = 0; j < CARD_WIDTH_COUNT; ++j)
        {
            if (cards[i][j] != nullptr && cards[i][j]->isInitialPosition())
            {
                propAni = new QPropertyAnimation(cards[i][j], "pos", this);
                propAni->setDuration(duration);
                propAni->setEasingCurve(QEasingCurve(QEasingCurve::InOutCubic));
                propAni->setKeyValueAt(0.0, cards[i][j]->pos());
                propAni->setKeyValueAt(1.0, QPoint(cards[i][j]->pos().x(), cards[i][j]->pos().y() + down->height()));
                selectAni->addAnimation(propAni);
            }
        }
    }
    QAbstractAnimation* ani = selectAni;
    ani->start(QAbstractAnimation::DeleteWhenStopped);
    QObject::connect(ani, SIGNAL(finished()), this, SLOT(slotSceneLeftAnimation()));
}

void QGameDayInterface::slotSceneLeftAnimation()
{
    QParallelAnimationGroup *startAni = new QParallelAnimationGroup(this);
    QPropertyAnimation *propAni;

    propAni = new QPropertyAnimation(background, "pos", this);
    propAni->setDuration(1500);
    propAni->setEasingCurve(QEasingCurve(QEasingCurve::InOutCubic));
    propAni->setKeyValueAt(0.0, QPoint(-500, 0));
    propAni->setKeyValueAt(1.0, QPoint(-120, 0));
    startAni->addAnimation(propAni);

    for (int i = 0; i < START_ZOMBIE_COUNT; ++i)
    {
        propAni = new QPropertyAnimation(zombie[i], "pos", this);
        propAni->setDuration(1500);
        propAni->setEasingCurve(QEasingCurve(QEasingCurve::InOutCubic));
        propAni->setKeyValueAt(0.0, QPoint(p[i], q[i]));
        propAni->setKeyValueAt(1.0, QPoint(p[i] + 380, q[i]));
        startAni->addAnimation(propAni);
    }
    QAbstractAnimation* ani = startAni;
    ani->start(QAbstractAnimation::DeleteWhenStopped);
    QObject::connect(ani, SIGNAL(finished()), this, SLOT(slotStart()));
}

void QGameDayInterface::slotStart()
{
    if (cardPlantMapper != nullptr) delete cardPlantMapper;
    cardPlantMapper = new QSignalMapper(this);
    QObject::connect(cardPlantMapper, SIGNAL(mapped(int)), this, SLOT(slotPlant(int)));
    for (int i = 0; i < CARD_CAN_USE; ++i)
    {
        QObject::connect(cardsCanUse[i], SIGNAL(clicked(bool)), cardPlantMapper, SLOT(map()));
        cardPlantMapper->setMapping(cardsCanUse[i], i);
    }
    background->hide();
    timerID = this->startTimer(TIME_ELAPSE);
}

void QGameDayInterface::slotClickSunshine(int label)
{
    if (sunshines[label]->isClicked()) return;
    curSunshine += SUNSHINE_VALUE;
    sunshines[label]->setClicked();
    sunshines[label]->setDestination(SUNSHINE_DEST_X, SUNSHINE_DEST_Y);
    sunshines[label]->setSpeed((SUNSHINE_DEST_X - sunshines[label]->pos().x()) / (SUNSHINE_RUN / TIME_ELAPSE),
                               (SUNSHINE_DEST_Y - sunshines[label]->pos().y()) / (SUNSHINE_RUN / TIME_ELAPSE));
    int dummy = sunshines[label]->getGenerateID();
    if (plantsID.find(dummy) != plantsID.end())
    {
        plants[dummy]->setClicked();
    }
}

void QGameDayInterface::slotMoveCard(int pos)
{
    int i = pos / CARD_WIDTH_COUNT;
    int j = pos % CARD_WIDTH_COUNT;
    if (cards[i][j]->pos() != QPoint(10 + j * 52, 120 + i * 80))
    {
        cards[i][j]->setInitialPosition();
        for (int k = 0; k <= cardsTop; ++k)
        {
            if (cardsCanUse[k] == cards[i][j])
            {
                for (int k0 = k; k0 < cardsTop; ++k0)
                {
                    cardsCanUse[k0] = cardsCanUse[k0 + 1];
                    cardsCanUse[k0]->setGeometry(81 + k0 * 50, 10, 0, 0);
                }
                cardsCanUse[cardsTop--] = nullptr;
                break;
            }
        }
    }
    else if (cardsTop < CARD_CAN_USE - 1)
    {
        cardsCanUse[++cardsTop] = cards[i][j];
        cards[i][j]->setGeometry(81 + cardsTop * 50, 10, 0, 0);
    }
}

void QGameDayInterface::slotClickStart()
{
    if (cardsTop != CARD_CAN_USE - 1)
    {
        QMessageBox* msgbox = new QMessageBox(this);
        msgbox->setText("卡片不足，请继续选择！");
        msgbox->setIcon(QMessageBox::Warning);
        msgbox->setStandardButtons(QMessageBox::Ok);
        if (msgbox->exec() == QMessageBox::Ok)
        {
            delete msgbox;
        }
    }
    else
    {
        slotBacktoSceneAnimation();
    }
}

void QGameDayInterface::slotPlant(int label)
{
    qDebug() << "good plant";
    mouseLabel = label;
    mousePic->resize(cardsCanUse[mouseLabel]->staticPic.size());
    //mousePic->setPixmap(cardsCanUse[mouseLabel]->staticPic);

    int alpha = 150;
    QImage beforeImg = cardsCanUse[mouseLabel]->staticPic.toImage();
    QImage nowImg = cardsCanUse[mouseLabel]->staticPic.toImage();
    QPainter painter(&nowImg);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(nowImg.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, beforeImg);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter.fillRect(nowImg.rect(), QColor(0, 0, 0, alpha));
    painter.end();

    QPixmap before = QPixmap::fromImage(beforeImg);
    QPixmap now = QPixmap::fromImage(nowImg);
    QPoint p = this->mapFromGlobal(this->cursor().pos());

    mouseShadow->setPixmap(now);
    mouseShadow->resize(now.size());
    mouseShadow->raise();

    mousePic->setPixmap(before);
    mousePic->resize(before.size());
    mousePic->setGeometry(p.x() - mousePic->width() / 2, p.y() - mousePic->height() / 2, mousePic->width(), mousePic->height());
    mousePic->show();
    mousePic->raise();
}
