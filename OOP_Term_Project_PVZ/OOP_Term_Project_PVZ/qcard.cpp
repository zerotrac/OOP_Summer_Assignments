#include "qcard.h"

QCard::QCard()
{
    QSize size = QSize(100, 140) * 0.48;
    this->setFixedSize(size);
    this->setIconSize(size);
    this->setIcon(QPixmap("Resources/interface/card_background.png"));
    this->setCursor(Qt::PointingHandCursor);

    labelPic = new QLabel(this);
    QPixmap pic = QPixmap("Resources/plants/peashooter/static.gif").scaled(QSize(37, 37));
    labelPic->setPixmap(pic);
    labelPic->setGeometry(7, 11, 37, 37);

    sunshineCost = 100;
    labelTxt = new QLabel(this);
    labelTxt->setText(QString::number(sunshineCost));
    labelTxt->setGeometry(8, 53, 25, 10);
}

QCard::~QCard()
{

}
