#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>
#include <QLayout>
#include <QString>
#include <QStringList>
#include <QAction>
#include <QDialog>
#include <QDateEdit>
#include <QPushButton>
#include <QSpacerItem>
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
    QMenuBar* menubar;
    QWidget* widget;
    QLabel** labels;
    QDialog* dialog;
    QMessageBox* msgbox;
    QDateEdit* dialogDate;

private slots:
    void dialogShow();
    void modifyDate();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
