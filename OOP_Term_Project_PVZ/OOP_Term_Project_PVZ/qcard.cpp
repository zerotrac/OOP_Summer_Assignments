#include "qcard.h"

QCard::QCard()
{
    QSize size = QSize(100, 140) * 0.48;
    this->setFixedSize(size);
    this->setIconSize(size);
    this->setIcon(QPixmap("Resources/interface/card_background.png"));
    this->setCursor(Qt::PointingHandCursor);

    labelPic = new QLabel(this);
    labelPic->setGeometry(7, 11, 37, 37);

    labelTxt = new QLabel(this);
    labelTxt->setGeometry(8, 53, 25, 10);
}

QCard::~QCard()
{

}

void QCard::initialize()
{
    cd = 0;
    setInitialPosition();
}

bool QCard::isInitialPosition() const
{
    int i = id / 8;
    int j = id % 8;
    return (this->pos() == QPoint(10 + j * 52, 120 + i * 80));
}

void QCard::setInitialPosition()
{
    int i = id / 8;
    int j = id % 8;
    this->setGeometry(10 + j * 52, 120 + i * 80, 0, 0);
}

void QCard::updateInfo(int sunshine)
{
    --cd;
    if (cd < 0) cd = 0;
    if (sunshine >= sunshineCost)
    {
        this->setEnabled(true);
    }
    else
    {
        this->setEnabled(false);
    }
}

bool QCard::canGetPlant()
{
    return (cd <= 0);
}

