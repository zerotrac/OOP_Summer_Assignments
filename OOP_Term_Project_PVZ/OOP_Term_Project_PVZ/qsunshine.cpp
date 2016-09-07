#include "qsunshine.h"

QSunshine::QSunshine(int _ID)
{
    ID = _ID;
    value = SUNSHINE_VALUE;
    clicked = false;

    countPic = 1;
    for (int i = 0; i < countPic; ++i)
    {
        QPixmap dummy("Resources/sunshine/sun.gif");
        dummy = dummy.scaled(dummy.width() * 0.75, dummy.height() * 0.75);
        pics.push_back(dummy);

    }
    currentPic = 0;
    this->setMask(pics[0].mask());
    this->setFixedSize(pics[0].size());
    this->setIcon(pics[0]);
    this->setIconSize(pics[0].size());
    this->setStyleSheet("QPushButton {border: none;}"
                        "QPushButton:hover {border: none;}"
                        "QPushButton:pressed {border: none;}");
    this->setCursor(Qt::PointingHandCursor);
}

QSunshine::~QSunshine()
{
    pics.clear();
}

void QSunshine::updateInfo()
{
    posX += spdX;
    posY += spdY;
    if ((spdX < 0 && posX < destX) || (spdX > 0 && posX > destX)) posX = destX;
    if ((spdY < 0 && posY < destY) || (spdY > 0 && posY > destY)) posY = destY;
    this->setGeometry(posX, posY, 0, 0);
}

void QSunshine::setGenerateID(int _generateID)
{
    generateID = _generateID;
}

void QSunshine::setAxis(double dx, double dy)
{
    posX = dx;
    posY = dy - this->height();
    this->setGeometry(posX, posY, 0, 0);
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

void QSunshine::setClicked()
{
    clicked = true;
}

bool QSunshine::isClicked() const
{
    return clicked;
}

int QSunshine::getGenerateID() const
{
    return generateID;
}
