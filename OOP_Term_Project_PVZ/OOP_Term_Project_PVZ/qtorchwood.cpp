#include "QTorchwood.h"

QTorchwood::QTorchwood(int _id)
{
    id = _id;
    atk = baseAtk = 0;
    hp = baseHp = 300;
    cd = baseCd = 0;
    rng = baserng = 0;
    bullet = 1;
    shell = 0;
    spdX = spdY = baseSpdX = baseSpdY = 0;
    weapon = nullptr;

    countPic = 1;
    for (int i = 0; i < countPic; ++i)
    {
        QMovie* dummy = new QMovie("Resources/plants/torchwood/" + QString::number(i) + ".gif");
        dummy->start();
        pics.push_back(dummy);
    }
    currentPic = 0;
    this->setFixedSize(QPixmap("Resources/plants/torchwood/0.gif").size());
    this->setMovie(pics[currentPic]);
}

QTorchwood::~QTorchwood()
{

}

bool QTorchwood::canAttack()
{
    return false;
}

std::vector<QWeapon*> QTorchwood::attack()
{
    std::vector<QWeapon*> weapons;
    return weapons;
}

bool QTorchwood::canGenerateSunshine()
{
    return false;
}

QSunshine* QTorchwood::generateSunshine()
{
    return nullptr;
}

bool QTorchwood::isMushroom()
{
    return false;
}

bool QTorchwood::canLitUp()
{
    return true;
}

void QTorchwood::updateInfo()
{

}
