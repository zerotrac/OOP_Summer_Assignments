#ifndef QSNOWPEACARD_H
#define QSNOWPEACARD_H

#include "qcard.h"
#include "src_plants/qsnowpea.h"

class QSnowPeaCard: public QCard
{
    Q_OBJECT

public:
    QSnowPeaCard(int _id);
    virtual ~QSnowPeaCard();

public:
    virtual QPlant* getPlant(int _id);

};

#endif // QSNOWPEACARD_H
