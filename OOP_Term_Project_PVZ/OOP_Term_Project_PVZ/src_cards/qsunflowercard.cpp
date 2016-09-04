#include "qsunflowercard.h"

QSunflowerCard::QSunflowerCard(int _id)
{
    staticPic.load("Resources/plants/sunflower/static.gif");
    id = _id;
    baseCd = 7.5 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/sunflower/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 50;
    labelTxt->setText(QString::number(sunshineCost));
}

QSunflowerCard::~QSunflowerCard()
{

}

QPlant* QSunflowerCard::getPlant(int _id)
{
    cd = baseCd;
    return new QSunflower(_id);
}
