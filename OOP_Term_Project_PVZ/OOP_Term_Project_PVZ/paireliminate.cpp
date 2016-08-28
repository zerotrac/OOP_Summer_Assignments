#include "paireliminate.h"
#include "ui_paireliminate.h"

PairEliminate::PairEliminate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PairEliminate)
{
    ui->setupUi(this);
}

PairEliminate::~PairEliminate()
{
    delete ui;
}
