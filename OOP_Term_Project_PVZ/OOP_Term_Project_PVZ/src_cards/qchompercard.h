#ifndef QCHOMPERCARD_H
#define QCHOMPERCARD_H

#include "qcard.h"
#include "src_plants/qchomper.h"

class QChomperCard: public QCard
{
    Q_OBJECT

public:
    QChomperCard(int _id);
    virtual ~QChomperCard();

public:
    virtual QPlant* getPlant(int _id);
};

#endif // QCHOMPERCARD_H
