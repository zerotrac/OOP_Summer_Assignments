#ifndef QPEASHOOTERCARD_H
#define QPEASHOOTERCARD_H

#include "qcard.h"
#include "src_plants/qpeashooter.h"

class QPeashooterCard: public QCard
{
    Q_OBJECT

public:
    QPeashooterCard(int _id);
    virtual ~QPeashooterCard();

public:
    virtual QPlant* getPlant(int _id);

};

#endif // QPEASHOOTERCARD_H
