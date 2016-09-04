#include "qsnowpeacard.h"

QSnowPeaCard::QSnowPeaCard(int _id)
{
    staticPic.load("Resources/plants/snowpea/static.gif");
    id = _id;
    baseCd = 7.5 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/snowpea/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 175;
    labelTxt->setText(QString::number(sunshineCost));
}

QSnowPeaCard::~QSnowPeaCard()
{

}

QPlant* QSnowPeaCard::getPlant(int _id)
{
    cd = baseCd;
    return new QSnowPea(_id);
}
