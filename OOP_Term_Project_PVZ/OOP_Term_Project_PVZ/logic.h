#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include "const.h"
#include "mainwindow.h"
#include "paireliminate.h"

class Logic : public QObject
{
    Q_OBJECT
public:
    explicit Logic(QObject *parent = 0);

public:
    MainWindow* mainwindow;
    PairEliminate* pairEliminate;

public:
    void execute();
};

#endif // LOGIC_H
