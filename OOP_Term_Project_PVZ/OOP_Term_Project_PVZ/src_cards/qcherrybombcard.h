#ifndef QCHERRYBOMBCARD_H
#define QCHERRYBOMBCARD_H

#include "qcard.h"
#include "src_plants/qcherrybomb.h"

class QCherryBombCard: public QCard
{
    Q_OBJECT

public:
    QCherryBombCard(int _id);
    virtual ~QCherryBombCard();

public:
    virtual QPlant* getPlant(int _id);
};

#endif // QCHERRYBOMBCARD_H
