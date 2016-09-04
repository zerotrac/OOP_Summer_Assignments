#include "qdoublepeacard.h"

QDoublePeaCard::QDoublePeaCard(int _id)
{
    id = _id;
    baseCd = 7.5 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/doublepea/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 200;
    labelTxt->setText(QString::number(sunshineCost));
}

QDoublePeaCard::~QDoublePeaCard()
{

}

QPlant* QDoublePeaCard::getPlant(int _id)
{
    cd = baseCd;
    return new QDoublePea(_id);
}
