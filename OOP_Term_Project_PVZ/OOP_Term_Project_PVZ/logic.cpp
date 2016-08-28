#include "logic.h"

Logic::Logic(QObject *parent) : QObject(parent)
{
    mainwindow = new MainWindow();
    mainwindow->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));

    pairEliminate = new PairEliminate();
    mainwindow->setCentralWidget(pairEliminate);
}

void Logic::execute()
{
    mainwindow->show();
}
