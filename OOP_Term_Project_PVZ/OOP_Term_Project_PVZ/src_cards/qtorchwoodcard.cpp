#include "qtorchwoodcard.h"

QTorchwoodCard::QTorchwoodCard(int _id)
{
    id = _id;
    baseCd = 7.5 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/torchwood/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 175;
    labelTxt->setText(QString::number(sunshineCost));
}

QTorchwoodCard::~QTorchwoodCard()
{

}

QPlant* QTorchwoodCard::getPlant(int _id)
{
    cd = baseCd;
    return new QTorchwood(_id);
}
