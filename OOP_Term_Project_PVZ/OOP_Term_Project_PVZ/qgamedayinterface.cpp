#include "qgamedayinterface.h"
#include "ui_qgamedayinterface.h"
#include <iostream>

QGameDayInterface::QGameDayInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGameDayInterface)
{
    ui->setupUi(this);

    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap backgroundBig("Resources/interface/day_background.jpg");
    QPixmap background = backgroundBig.copy(120, 0, 900, 600);
    palette.setBrush(QPalette::Background, QBrush(background));
    this->setPalette(palette);

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
        if (sunshine != nullptr)
        {
            QObject::disconnect(sunshine);
            delete sunshine;
        }
    }
    plants.clear();
    enemies.clear();
    sunshines.clear();

    sunshineMapper = nullptr;
    if (sunshineMapper != nullptr)
    {
        QObject::disconnect(sunshineMapper);
        delete sunshineMapper;
    }
    sunshineMapper = new QSignalMapper(this);
    QObject::connect(sunshineMapper, SIGNAL(mapped(int)), this, SLOT(slotClickSunshine(int)));
    plantLabel = -1;
    enemyLabel = -1;
    sunshineLabel = -1;
    curSunshine = 0;

    qDebug() << "good1";

    for (int i = 0; i < 5; ++i)
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

            plt->setAxis(145 + j * 80, 170 + i * 95);
            plt->setParent(this);
            plantsID.insert(plantLabel);
            plants.push_back(plt);
        }
    }
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 7; j < 9; ++j)
        {
            ++enemyLabel;
            QPlant* plt;
            if (j == 7) plt = new QWallnut(plantLabel);
            else plt = new QPeashooter(plantLabel);
            plt->setAxis(145 + j * 80, 170 + i * 95);
            plt->setParent(this);
            enemiesID.insert(enemyLabel);
            enemies.push_back(plt);
        }
    }

    timerID = this->startTimer(TIME_ELAPSE);
}

QGameDayInterface::~QGameDayInterface()
{
    delete ui;
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
    //qDebug() << "sun =" << curSunshine;
    if (event->timerId() == timerID)
    {
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
                    qDebug() << "weapon location =" << weapon->pos().x() << weapon->pos().y();
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
