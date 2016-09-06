#include "qscaredyshroomcard.h"

QScaredyShroomCard::QScaredyShroomCard(int _id)
{
    staticPic.load("Resources/plants/scaredyshroom/static.gif");
    id = _id;
    baseCd = 7.5 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/scaredyshroom/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 25;
    labelTxt->setText(QString::number(sunshineCost));
}

QScaredyShroomCard::~QScaredyShroomCard()
{

}

QPlant* QScaredyShroomCard::getPlant(int _id)
{
    cd = baseCd;
    return new QScaredyShroom(_id);
}
