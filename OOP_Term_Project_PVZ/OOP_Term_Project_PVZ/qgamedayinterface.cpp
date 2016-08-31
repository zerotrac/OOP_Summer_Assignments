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
    plants[1]->setAxis(100, 225);
    plants[1]->setParent(this);
    plants[2] = new QSnowPea(2);
    plants[2]->setAxis(100, 350);
    plants[2]->setParent(this);
    plants[3] = new QDoublePea(3);
    plants[3]->setAxis(100, 475);
    plants[3]->setParent(this);
    plants[4] = new QGatlingPea(4);
    plants[4]->setAxis(100, 600);
    plants[4]->setParent(this);
    for (int i = 5; i < 10; ++i)
    {
        plants[i] = new QTorchwood(i);
        plants[i]->setAxis(400, 100 + 125 * (i - 5));
        plants[i]->setParent(this);
    }
    plants[10] = new QTorchwood(10);
    plants[10]->setAxis(600, 350);
    plants[10]->setParent(this);

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
            for (int j = 0; j < 11; ++j)
            {
                if (weapon->inRange(plants[j]) && plants[j]->canLitUp())
                {
                    weapon->setLit(plants[j]->id);
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
        for (int i = 0; i < 11; ++i)
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
