#include "qpuffshroomcard.h"

QPuffShroomCard::QPuffShroomCard(int _id)
{
    staticPic.load("Resources/plants/puffshroom/static.gif");
    id = _id;
    baseCd = 7.5 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/puffshroom/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 0;
    labelTxt->setText(QString::number(sunshineCost));
}

QPuffShroomCard::~QPuffShroomCard()
{

}

QPlant* QPuffShroomCard::getPlant(int _id)
{
    cd = baseCd;
    return new QPuffShroom(_id);
}
