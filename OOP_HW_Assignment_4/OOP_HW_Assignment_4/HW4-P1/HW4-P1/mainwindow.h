#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSignalMapper>
#include <QLCDNumber>
#include <QLayout>
#include <QMessageBox>

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
    QGridLayout* layout;
    QSignalMapper* mapper;
    QPushButton** buttons;
    QLCDNumber* lcdnumber;
    QMessageBox* helpmsg;
    QString value;

private slots:
    void lcdAppend(int digit);
    void lcdClear();
    void showHelpDialog();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
