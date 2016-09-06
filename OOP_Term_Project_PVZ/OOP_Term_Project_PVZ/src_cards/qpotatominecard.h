#ifndef QPOTATOMINECARD_H
#define QPOTATOMINECARD_H

#include "qcard.h"
#include "src_plants/qpotatomine.h"

class QPotatoMineCard: public QCard
{
    Q_OBJECT

public:
    QPotatoMineCard(int _id);
    virtual ~QPotatoMineCard();

public:
    virtual QPlant* getPlant(int _id);
};

#endif // QPOTATOMINECARD_H
