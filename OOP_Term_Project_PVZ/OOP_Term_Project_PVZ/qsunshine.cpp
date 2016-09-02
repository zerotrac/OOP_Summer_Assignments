#include "qsunshine.h"

QSunshine::QSunshine(int _ID)
{
    value = SUNSHINE_VALUE;
    ID = _ID;

    countPic = 1;
    for (int i = 0; i < countPic; ++i)
    {
        QPixmap dummy("Resources/sunshine/sun.gif");
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setMask(pics[0].mask());
    this->setFixedSize(pics[0].size());
    this->setStyleSheet("QPushButton {background-image: url(Resources/sunshine/sun.gif);}"
                        "QPushButton:hover {background-image: url(Resources/sunshine/sun.gif);}"
                        "QPushButton:pressed {background-image: url(Resources/sunshine/sun.gif);}");
}

QSunshine::~QSunshine()
{

}

void QSunshine::updateInfo()
{
    this->setGeometry(this->pos().x() + spdX, this->pos().y() + spdY, 0, 0);
    int posX = this->pos().x();
    int posY = this->pos().y();
    if ((spdX < 0 && posX < destX) || (spdX > 0 && posX > destX))
    {
        this->setGeometry(destX, this->pos().y(), 0, 0);
    }
    if ((spdY < 0 && posY < destY) || (spdY > 0 && posY > destY))
    {
        this->setGeometry(this->pos().x(), destY, 0, 0);
    }
}

void QSunshine::setGenerateID(int _generateID)
{
    generateID = _generateID;
}

void QSunshine::setAxis(double dx, double dy)
{
    this->setGeometry(dx, dy - this->height(), 0, 0);
}

void QSunshine::setSpeed(double dx, double dy)
{
    spdX = dx;
    spdY = dy;
}

void QSunshine::setDestination(double dx, double dy)
{
    destX = dx;
    destY = dy;
}
