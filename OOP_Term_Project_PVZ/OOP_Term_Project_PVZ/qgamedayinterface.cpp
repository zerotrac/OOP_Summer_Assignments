#include "qgamedayinterface.h"
#include "ui_qgamedayinterface.h"

QGameDayInterface::QGameDayInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGameDayInterface)
{
    ui->setupUi(this);

    QPeashooter* pea = new QPeashooter(0);
    pea->setParent(this);
}

QGameDayInterface::~QGameDayInterface()
{
    delete ui;
}
