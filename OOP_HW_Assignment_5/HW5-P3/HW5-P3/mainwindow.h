#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

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
    QPixmap** pics;
    QWidget* widget;
    QPushButton* button;
    QPushButton* left;
    QPushButton* right;
    int size;
    int cur;

private slots:
    void picIncrement();
    void picDecrement();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
