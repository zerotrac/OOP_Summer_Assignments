#include "qgamedayinterface.h"
#include "ui_qgamedayinterface.h"
#include <iostream>

QGameDayInterface::QGameDayInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGameDayInterface)
{
    ui->setupUi(this);

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
    plants.clear();
    enemies.clear();
    plantLabel = -1;
    enemyLabel = -1;

    ++plantLabel;
    QPlant* plt = new QPeashooter(plantLabel);
    plt->setAxis(200, 100);
    plt->setParent(this);
    plantsID.insert(plantLabel);
    plants.push_back(plt);

    ++plantLabel;
    plt = new QSnowPea(plantLabel);
    plt->setAxis(200, 225);
    plt->setParent(this);
    plantsID.insert(plantLabel);
    plants.push_back(plt);

    ++plantLabel;
    plt = new QDoublePea(plantLabel);
    plt->setAxis(200, 350);
    plt->setParent(this);
    plantsID.insert(plantLabel);
    plants.push_back(plt);

    ++plantLabel;
    plt = new QGatlingPea(plantLabel);
    plt->setAxis(200, 475);
    plt->setParent(this);
    plantsID.insert(plantLabel);
    plants.push_back(plt);

    ++plantLabel;
    plt = new QGatlingPea(plantLabel);
    plt->setAxis(200, 600);
    plt->setParent(this);
    plantsID.insert(plantLabel);
    plants.push_back(plt);

    for (int i = 5; i < 10; ++i)
    {
        if (i == 8) continue;
        ++plantLabel;
        plt = new QTorchwood(plantLabel);
        plt->setAxis(350, 100 + 125 * (i - 5));
        plt->setParent(this);
        plantsID.insert(plantLabel);
        plants.push_back(plt);
    }

    ++plantLabel;
    plt = new QWallnut(plantLabel);
    plt->setAxis(50, 100);
    plt->setParent(this);
    plantsID.insert(plantLabel);
    plants.push_back(plt);

    for (int i = 0; i < 5; ++i)
    {
        ++enemyLabel;
        plt = new QWallnut(enemyLabel);
        plt->setAxis(650, 100 + 125 * i);
        plt->setParent(this);
        enemiesID.insert(enemyLabel);
        enemies.push_back(plt);

        ++enemyLabel;
        plt = new QWallnut(enemyLabel);
        plt->setAxis(800, 100 + 125 * i);
        plt->setParent(this);
        enemiesID.insert(enemyLabel);
        enemies.push_back(plt);
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
    if (event->timerId() == timerID)
    {
        // 步骤：
        // 1. 武器与其它单位进行判定，僵尸销毁
        // 2. 武器移动，武器销毁
        // 3. 植物攻击判定
        // 4. 僵尸攻击判定，植物销毁
        for (QWeapon* weapon: weapons)
        {
            for (int plantID: plantsID)
            {
                QPlant* plant = plants[plantID];
                if (weapon->inRange(plant) && plant->canLitUp())
                {
                    weapon->setLit(plantID);
                }
            }
            for (int enemyID: enemiesID)
            {
                QPlant* enemy = enemies[enemyID];
                if (weapon->inRange(enemy))
                {
                    enemy->beAttacked(weapon->atk);
                    if (enemy->isDead())
                    {
                        delete enemy;
                        enemiesID.erase(enemyID);
                    }
                    weapon->decBullet();
                }
            }
            if (weapon->outofDuration())
            {
                delete weapon;
                weapons.erase(weapon);
            }
        }
        for (QWeapon* weapon: weapons)
        {
            weapon->updateInfo();
            weapon->show();
        }
        for (int plantID: plantsID)
        {
            QPlant* plant = plants[plantID];
            if (plant->canAttack())
            {
                std::vector<QWeapon*> wps = plant->attack();
                for (QWeapon* wp: wps)
                {
                    wp->setAxis(plant->pos().x() + plant->width() / 2, plant->pos().y() + plant->height() / 2);
                    wp->setParent(this);
                    weapons.insert(wp);
                }
            }
            plant->updateInfo();
        }

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
