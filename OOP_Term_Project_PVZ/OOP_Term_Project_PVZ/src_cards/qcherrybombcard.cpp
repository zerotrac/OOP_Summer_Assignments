#include "qcherrybombcard.h"

QCherryBombCard::QCherryBombCard(int _id)
{
    staticPic.load("Resources/plants/cherrybomb/static.gif");
    id = _id;
    baseCd = 30 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/cherrybomb/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 50;
    labelTxt->setText(QString::number(sunshineCost));
}

QCherryBombCard::~QCherryBombCard()
{

}

QPlant* QCherryBombCard::getPlant(int _id)
{
    cd = baseCd;
    return new QCherryBomb(_id);
}
