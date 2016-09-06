#include "qpotatominecard.h"

QPotatoMineCard::QPotatoMineCard(int _id)
{
    staticPic.load("Resources/plants/potatomine/static.gif");
    id = _id;
    baseCd = 30 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/potatomine/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 25;
    labelTxt->setText(QString::number(sunshineCost));
}

QPotatoMineCard::~QPotatoMineCard()
{

}

QPlant* QPotatoMineCard::getPlant(int _id)
{
    cd = baseCd;
    return new QPotatoMine(_id);
}
