#include "qwallnutcard.h"

QWallnutCard::QWallnutCard(int _id)
{
    staticPic.load("Resources/plants/wallnut/static.gif");
    id = _id;
    baseCd = 30 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/wallnut/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 50;
    labelTxt->setText(QString::number(sunshineCost));
}

QWallnutCard::~QWallnutCard()
{

}

QPlant* QWallnutCard::getPlant(int _id)
{
    cd = baseCd;
    return new QWallnut(_id);
}
