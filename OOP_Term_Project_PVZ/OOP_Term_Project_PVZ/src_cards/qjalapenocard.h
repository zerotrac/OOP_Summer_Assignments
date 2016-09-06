#ifndef QJALAPENOCARD_H
#define QJALAPENOCARD_H

#include "qcard.h"
#include "src_plants/qjalapeno.h"

class QJalapenoCard: public QCard
{
    Q_OBJECT

public:
    QJalapenoCard(int _id);
    virtual ~QJalapenoCard();

public:
    virtual QPlant* getPlant(int _id);
};

#endif // QJALAPENOCARD_H
