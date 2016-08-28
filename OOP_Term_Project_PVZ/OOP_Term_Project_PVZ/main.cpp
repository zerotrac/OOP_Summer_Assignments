#include <QApplication>
#include <ctime>

#include "logic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    srand(time(nullptr));

    Logic* logic = new Logic();
    logic->execute();

    return a.exec();
}
