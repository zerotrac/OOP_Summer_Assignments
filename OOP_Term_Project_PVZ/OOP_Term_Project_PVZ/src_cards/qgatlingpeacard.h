#ifndef QGATLINGPEACARD_H
#define QGATLINGPEACARD_H

#include "qcard.h"
#include "src_plants/qgatlingpea.h"

class QGatlingPeaCard: public QCard
{
    Q_OBJECT

public:
    QGatlingPeaCard(int _id);
    virtual ~QGatlingPeaCard();

public:
    virtual QPlant* getPlant(int _id);

};

#endif // QGATLINGPEACARD_H
