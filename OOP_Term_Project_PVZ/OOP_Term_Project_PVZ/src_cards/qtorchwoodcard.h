#ifndef QTORCHWOODCARD_H
#define QTORCHWOODCARD_H

#include "qcard.h"
#include "src_plants/qtorchwood.h"

class QTorchwoodCard: public QCard
{
    Q_OBJECT

public:
    QTorchwoodCard(int _id);
    virtual ~QTorchwoodCard();

public:
    virtual QPlant* getPlant(int _id);

};

#endif // QTORCHWOODCARD_H
