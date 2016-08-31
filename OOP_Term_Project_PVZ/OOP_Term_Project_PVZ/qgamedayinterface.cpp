#include "qgamedayinterface.h"
#include "ui_qgamedayinterface.h"
#include <iostream>

QGameDayInterface::QGameDayInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGameDayInterface)
{
    ui->setupUi(this);

    pea = new QPeashooter(0);
    pea->setAxis(200, 200);
    pea->setParent(this);

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
        while (head <= tail)
        {
            if (weapons[head]->outofDuration())
            {
                delete weapons[head];
                ++head;
            }
            else
            {
                break;
            }
        }
        for (int i = head; i <= tail; ++i)
        {
            weapons[i]->updateInfo();
            weapons[i]->show();
        }
        std::cout << pea->canAttack() << " " << head << " " << tail << std::endl;
        if (pea->canAttack())
        {
            std::vector<QWeapon*> wps = pea->attack();
            std::cout << "size = " << wps.size() << std::endl;
            for (QWeapon* wp: wps)
            {
                ++tail;
                wp->setAxis(pea->pos().x() + pea->width() / 2, pea->pos().y() + pea->height() / 2);
                wp->setParent(this);
                weapons.push_back(wp);
            }
        }
        pea->updateInfo();
    }
}
