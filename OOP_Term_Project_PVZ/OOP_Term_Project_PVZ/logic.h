#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <string>
#include "const.h"
#include "mainwindow.h"
#include "qinitialinterface.h"
#include "qgamedayinterface.h"
#include "paireliminate.h"

class Logic : public QObject
{
    Q_OBJECT
public:
    explicit Logic(QObject *parent = 0);

public:
    MainWindow* mainwindow;
    QInitialInterface* initialInterface;
    QGameDayInterface* gameDayInterface;
    PairEliminate* pairEliminate;

private:
    void makeConnections();

public:
    void execute();

signals:
    void signalWidget(QString);

private slots:
    void slotSetWidget(QString);
};

#endif // LOGIC_H
