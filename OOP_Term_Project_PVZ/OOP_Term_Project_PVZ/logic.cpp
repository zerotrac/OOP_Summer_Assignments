#include "logic.h"

Logic::Logic(QObject *parent) : QObject(parent)
{
    mainwindow = new MainWindow();
    mainwindow->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));

    initialInterface = new QInitialInterface();
    gameDayInterface = new QGameDayInterface();
    handbook = new QHandbook();
    pairEliminate = new PairEliminate();

    makeConnections();

    emit signalWidget(QString("main"));
}

void Logic::makeConnections()
{
    QObject::connect(this, SIGNAL(signalWidget(QString)), this, SLOT(slotSetWidget(QString)));
    QObject::connect(initialInterface, SIGNAL(signalWidget(QString)), this, SLOT(slotSetWidget(QString)));
    QObject::connect(pairEliminate, SIGNAL(signalWidget(QString)), this, SLOT(slotSetWidget(QString)));
    QObject::connect(handbook, SIGNAL(signalWidget(QString)), this, SLOT(slotSetWidget(QString)));
    QObject::connect(gameDayInterface, SIGNAL(signalWidget(QString)), this, SLOT(slotSetWidget(QString)));
}

void Logic::execute()
{
    mainwindow->show();
}

void Logic::slotSetWidget(QString s)
{
    std::cout << s.toStdString() << std::endl;
    mainwindow->takeCentralWidget();
    if (s.toLower() == QString("main")) mainwindow->setCentralWidget(initialInterface);
    if (s.toLower() == QString("eliminate"))
    {
        pairEliminate->gamePreparation();
        mainwindow->setCentralWidget(pairEliminate);
    }
    if (s.toLower() == QString("day"))
    {
        gameDayInterface->gamePreparation();
        mainwindow->setCentralWidget(gameDayInterface);
    }
    if (s.toLower() == QString("book"))
    {
        handbook->gamePreparation();
        mainwindow->setCentralWidget(handbook);
    }
}
