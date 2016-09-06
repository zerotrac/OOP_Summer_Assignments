#ifndef QICESHROOMCARD_H
#define QICESHROOMCARD_H

#include "qcard.h"
#include "src_plants/qiceshroom.h"

class QIceShroomCard: public QCard
{
    Q_OBJECT

public:
    QIceShroomCard(int _id);
    virtual ~QIceShroomCard();

public:
    virtual QPlant* getPlant(int _id);
};

#endif // QICESHROOMCARD_H
