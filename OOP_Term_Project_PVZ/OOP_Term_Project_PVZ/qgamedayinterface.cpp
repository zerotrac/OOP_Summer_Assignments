#include "qgamedayinterface.h"
#include "ui_qgamedayinterface.h"
#include <iostream>

QGameDayInterface::QGameDayInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGameDayInterface)
{
    ui->setupUi(this);

    plants[0] = new QPeashooter(0);
    plants[0]->setAxis(100, 100);
    plants[0]->setParent(this);
    plants[1] = new QSnowPea(1);
    plants[1]->setAxis(100, 250);
    plants[1]->setParent(this);
    plants[2] = new QDoublePea(2);
    plants[2]->setAxis(100, 400);
    plants[2]->setParent(this);
    plants[3] = new QGatlingPea(3);
    plants[3]->setAxis(100, 550);
    plants[3]->setParent(this);

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
        std::cout << "size = " << weapons.size() << std::endl;
        for (QWeapon* weapon: weapons)
        {
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
        for (int i = 0; i < 4; ++i)
        {
            if (plants[i]->canAttack())
            {
                std::vector<QWeapon*> wps = plants[i]->attack();
                //std::cout << "size = " << wps.size() << std::endl;
                for (QWeapon* wp: wps)
                {
                    wp->setAxis(plants[i]->pos().x() + plants[i]->width() / 2, plants[i]->pos().y() + plants[i]->height() / 2);
                    wp->setParent(this);
                    weapons.insert(wp);
                }
            }
            plants[i]->updateInfo();
        }
    }
}
