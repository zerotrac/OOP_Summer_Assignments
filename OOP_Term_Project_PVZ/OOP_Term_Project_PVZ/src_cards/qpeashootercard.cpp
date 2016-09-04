#include "qpeashootercard.h"

QPeashooterCard::QPeashooterCard(int _id)
{
    id = _id;
    baseCd = 7.5 * 1000 / TIME_ELAPSE;
    QPixmap pic = QPixmap("Resources/plants/peashooter/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);

    sunshineCost = 100;
    labelTxt->setText(QString::number(sunshineCost));
}

QPeashooterCard::~QPeashooterCard()
{

}

QPlant* QPeashooterCard::getPlant(int _id)
{
    cd = baseCd;
    return new QPeashooter(_id);
}
