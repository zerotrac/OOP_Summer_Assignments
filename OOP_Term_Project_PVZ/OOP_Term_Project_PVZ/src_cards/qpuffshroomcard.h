#ifndef QPUFFSHROOMCARD_H
#define QPUFFSHROOMCARD_H

#include "qcard.h"
#include "src_plants/qpuffshroom.h"

class QPuffShroomCard: public QCard
{
    Q_OBJECT

public:
    QPuffShroomCard(int _id);
    virtual ~QPuffShroomCard();

public:
    virtual QPlant* getPlant(int _id);
};

#endif // QPUFFSHROOMCARD_H
