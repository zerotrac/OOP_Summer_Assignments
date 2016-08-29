#include <QApplication>
#include <ctime>
#include "logic.h"

int main(int argc, char *argv[])
{
    std::srand(time(nullptr));

    QApplication a(argc, argv);

    Logic* logic = new Logic();
    logic->execute();

    return a.exec();
}
