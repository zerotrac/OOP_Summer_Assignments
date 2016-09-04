#include "qgatlingpeacard.h"

QGatlingPeaCard::QGatlingPeaCard(int _id)
{
    staticPic.load("Resources/plants/gatlingpea/static.gif");
    id = _id;
    baseCd = 50 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/gatlingpea/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 450;
    labelTxt->setText(QString::number(sunshineCost));
}

QGatlingPeaCard::~QGatlingPeaCard()
{

}

QPlant* QGatlingPeaCard::getPlant(int _id)
{
    cd = baseCd;
    return new QGatlingPea(_id);
}
