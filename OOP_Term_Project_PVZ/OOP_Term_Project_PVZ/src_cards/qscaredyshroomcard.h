#ifndef QSCAREDYSHROOMCARD_H
#define QSCAREDYSHROOMCARD_H

#include "qcard.h"
#include "src_plants/qscaredyshroom.h"

class QScaredyShroomCard: public QCard
{
    Q_OBJECT

public:
    QScaredyShroomCard(int _id);
    virtual ~QScaredyShroomCard();

public:
    virtual QPlant* getPlant(int _id);
};

#endif // QSCAREDYSHROOMCARD_H
