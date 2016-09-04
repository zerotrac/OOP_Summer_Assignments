#include "qtallnutcard.h"

QTallnutCard::QTallnutCard(int _id)
{
    staticPic.load("Resources/plants/tallnut/static.gif");
    id = _id;
    baseCd = 30 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/tallnut/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 125;
    labelTxt->setText(QString::number(sunshineCost));
}

QTallnutCard::~QTallnutCard()
{

}

QPlant* QTallnutCard::getPlant(int _id)
{
    cd = baseCd;
    return new QTallnut(_id);
}
