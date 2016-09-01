#include "qgamedayinterface.h"
#include "ui_qgamedayinterface.h"
#include <iostream>

QGameDayInterface::QGameDayInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGameDayInterface)
{
    ui->setupUi(this);

    plants.clear();

    QPlant* plt = new QPeashooter(0);
    plt->setAxis(200, 100);
    plt->setParent(this);
    plants.insert(plt);

    plt = new QSnowPea(1);
    plt->setAxis(200, 225);
    plt->setParent(this);
    plants.insert(plt);

    plt = new QDoublePea(2);
    plt->setAxis(200, 350);
    plt->setParent(this);
    plants.insert(plt);

    plt = new QGatlingPea(3);
    plt->setAxis(200, 475);
    plt->setParent(this);
    plants.insert(plt);

    plt = new QGatlingPea(4);
    plt->setAxis(200, 600);
    plt->setParent(this);
    plants.insert(plt);

    for (int i = 5; i < 10; ++i)
    {
        if (i == 8) continue;
        plt = new QTorchwood(i);
        plt->setAxis(350, 100 + 125 * (i - 5));
        plt->setParent(this);
        plants.insert(plt);
    }

    plt = new QWallnut(11);
    plt->setAxis(50, 100);
    plt->setParent(this);
    plants.insert(plt);

    enemies.clear();
    for (int i = 0; i < 5; ++i)
    {
        plt = new QWallnut(i * 2);
        plt->setAxis(650, 100 + 125 * i);
        plt->setParent(this);
        enemies.insert(plt);

        plt = new QWallnut(i * 2 + 1);
        plt->setAxis(800, 100 + 125 * i);
        plt->setParent(this);
        enemies.insert(plt);
    }
    timerID = this->startTimer(TIME_ELAPSE);
    weapons.clear();
}

QGameDayInterface::~QGameDayInterface()
{
    delete ui;
}

void QGameDayInterface::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerID)
    {
        //std::cout << "size = " << weapons.size() << std::endl;
        for (QWeapon* weapon: weapons)
        {
            qDebug() << "weapon atk = " << weapon->atk;
            for (QPlant* plant: plants)
            {
                if (weapon->inRange(plant) && plant->canLitUp())
                {
                    weapon->setLit(plant->id);
                }
            }
            for (QPlant* enemy: enemies)
            {
                qDebug() << "enemy hp = " << enemy->getCurrentHP();
                if (weapon->inRange(enemy))
                {
                    enemy->beAttacked(weapon->atk);
                    if (enemy->isDead())
                    {
                        delete enemy;
                        enemies.erase(enemy);
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
        //std::cout << pea->canAttack() << " " << head << " " << tail << std::endl;
        for (QPlant* plant: plants)
        {
            if (plant->canAttack())
            {
                std::vector<QWeapon*> wps = plant->attack();
                //std::cout << "size = " << wps.size() << std::endl;
                for (QWeapon* wp: wps)
                {
                    wp->setAxis(plant->pos().x() + plant->width() / 2, plant->pos().y() + plant->height() / 2);
                    wp->setParent(this);
                    weapons.insert(wp);
                }
            }
            plant->updateInfo();
        }
        for (QPlant* enemy: enemies)
        {
            enemy->updateInfo();
        }
    }
}
