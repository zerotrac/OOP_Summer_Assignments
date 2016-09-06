#include "qjalapenocard.h"

QJalapenoCard::QJalapenoCard(int _id)
{
    staticPic.load("Resources/plants/jalapeno/static.gif");
    id = _id;
    baseCd = 50 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/jalapeno/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 125;
    labelTxt->setText(QString::number(sunshineCost));
}

QJalapenoCard::~QJalapenoCard()
{

}

QPlant* QJalapenoCard::getPlant(int _id)
{
    cd = baseCd;
    return new QJalapeno(_id);
}

