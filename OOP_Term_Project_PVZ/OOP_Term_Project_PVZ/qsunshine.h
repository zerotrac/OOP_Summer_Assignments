#ifndef QSUNSHINE_H
#define QSUNSHINE_H

#include <QWidget>
#include <QPixmap>

class QSunshine : public QWidget
{
    Q_OBJECT

public:
    explicit QSunshine(QWidget *parent = 0);
    virtual ~QSunshine();

private:
    int plantID; // 对应植物的编号（在拾取某个植物生产的阳光前，这个植物无论如何都不会再生产阳光）
    int value; // 阳光值
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
