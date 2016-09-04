#ifndef QCARD_H
#define QCARD_H

#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <qplant.h>

class QCard: public QPushButton
{
    Q_OBJECT

public:
    QCard();
    virtual ~QCard();

public:
    QPixmap staticPic;

protected:
    int id;
    QLabel* labelPic;
    QLabel* labelTxt;
    int sunshineCost;
    int cd;
    int baseCd;

public:
    void initialize();
    bool isInitialPosition() const;
    void setInitialPosition();
    void updateInfo(int sunshine);
    bool canGetPlant();
    virtual QPlant* getPlant(int _id) = 0;
};

#endif // QCARD_H
