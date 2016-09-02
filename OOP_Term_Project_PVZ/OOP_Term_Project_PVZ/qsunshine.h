#ifndef QSUNSHINE_H
#define QSUNSHINE_H

#include <QPushButton>
#include <QPixmap>

class QSunshine: public QPushButton
{
    Q_OBJECT

public:
    QSunshine();
    virtual ~QSunshine();

private:
    int value; // 阳光值
    int generateID;
    double spdX;
    double spdY;
    double posX; // 位置
    double posY;
    double destX;
    double destY;

protected:
    std::vector<QPixmap> pics;
    int currentPic;
};

#endif // QSUNSHINE_H
