#include <QApplication>
#include <ctime>
#include <QDir>
#include "logic.h"

int main(int argc, char *argv[])
{
    std::srand(time(nullptr));
    QApplication a(argc, argv);
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    Logic* logic = new Logic();
    logic->execute();

    return a.exec();
}
