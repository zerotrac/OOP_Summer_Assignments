#ifndef QSUNFLOWERCARD_H
#define QSUNFLOWERCARD_H

#include "qcard.h"
#include "src_plants/qsunflower.h"

class QSunflowerCard: public QCard
{
    Q_OBJECT

public:
    QSunflowerCard(int _id);
    virtual ~QSunflowerCard();

public:
    virtual QPlant* getPlant(int _id);

};

#endif // QSUNFLOWERCARD_H
