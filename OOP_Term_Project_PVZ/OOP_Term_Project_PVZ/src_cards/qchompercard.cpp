#include "qchompercard.h"

QChomperCard::QChomperCard(int _id)
{
    staticPic.load("Resources/plants/chomper/static.gif");
    id = _id;
    baseCd = 7.5 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/chomper/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 150;
    labelTxt->setText(QString::number(sunshineCost));
}

QChomperCard::~QChomperCard()
{

}

QPlant* QChomperCard::getPlant(int _id)
{
    cd = baseCd;
    return new QChomper(_id);
}
