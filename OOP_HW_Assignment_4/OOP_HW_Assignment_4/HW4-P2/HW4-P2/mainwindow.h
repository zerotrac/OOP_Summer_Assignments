#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDial>
#include <QLayout>
#include <QGroupBox>
#include <QLCDNumber>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget* widget;
    QGroupBox* boxCel;
    QGroupBox* boxFeh;
    QDial* dialCel;
    QDial* dialFeh;
    QLCDNumber* numberCel;
    QLCDNumber* numberFeh;

private slots:
    void adjustCel(int value);
    void adjustFeh(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
