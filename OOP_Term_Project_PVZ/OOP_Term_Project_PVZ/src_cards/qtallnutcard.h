#ifndef QTALLNUTCARD_H
#define QTALLNUTCARD_H

#include "qcard.h"
#include "src_plants/qtallnut.h"

class QTallnutCard: public QCard
{
    Q_OBJECT

public:
    QTallnutCard(int _id);
    virtual ~QTallnutCard();

public:
    virtual QPlant* getPlant(int _id);
};

#endif // QTALLNUTCARD_H
