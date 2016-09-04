#ifndef QDOUBLEPEACARD_H
#define QDOUBLEPEACARD_H

#include "qcard.h"
#include "src_plants/qdoublepea.h"

class QDoublePeaCard: public QCard
{
    Q_OBJECT

public:
    QDoublePeaCard(int _id);
    virtual ~QDoublePeaCard();

public:
    virtual QPlant* getPlant(int _id);

};

#endif // QDOUBLEPEACARD_H
