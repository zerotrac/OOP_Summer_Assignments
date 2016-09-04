#ifndef QWALLNUTCARD_H
#define QWALLNUTCARD_H

#include "qcard.h"
#include "src_plants/qwallnut.h"

class QWallnutCard: public QCard
{
    Q_OBJECT

public:
    QWallnutCard(int _id);
    virtual ~QWallnutCard();

public:
    virtual QPlant* getPlant(int _id);
};

#endif // QWALLNUTCARD_H
