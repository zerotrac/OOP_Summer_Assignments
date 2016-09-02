#ifndef QSUNSHINE_H
#define QSUNSHINE_H

#include <QPushButton>
#include <QBitmap>
#include <QPixmap>
#include "const.h"

class QSunshine: public QPushButton
{
    Q_OBJECT

public:
    QSunshine(int _ID);
    virtual ~QSunshine();

public:
    int ID;

private:
    int value; // 阳光值
    int generateID;
    double posX;
    double posY;
    double spdX;
    double spdY;
    double destX;
    double destY;
    bool clicked;

protected:
    std::vector<QPixmap> pics;
    int countPic;
    int currentPic;

public:
    virtual void updateInfo();
    void setGenerateID(int _generateID);
    void setAxis(double dx, double dy);
    void setSpeed(double dx, double dy);
    void setDestination(double dx, double dy);
    void setClicked();
    bool isClicked() const;
    int getGenerateID() const;
};

#endif // QSUNSHINE_H
