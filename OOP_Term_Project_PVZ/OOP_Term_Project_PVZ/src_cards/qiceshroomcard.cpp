#include "qiceshroomcard.h"

QIceShroomCard::QIceShroomCard(int _id)
{
    staticPic.load("Resources/plants/iceshroom/static.gif");
    id = _id;
    baseCd = 50 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/iceshroom/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 75;
    labelTxt->setText(QString::number(sunshineCost));
}

QIceShroomCard::~QIceShroomCard()
{

}

QPlant* QIceShroomCard::getPlant(int _id)
{
    cd = baseCd;
    return new QIceShroom(_id);
}
