#ifndef QCARD_H
#define QCARD_H

#include <QPushButton>
#include <QPixmap>
#include <QLabel>

class QCard: public QPushButton
{
    Q_OBJECT

public:
    QCard();
    virtual ~QCard();

private:
    QLabel* labelPic;
    QLabel* labelTxt;
    int sunshineCost;
    int cd;
    int baseCd;
};

#endif // QCARD_H
