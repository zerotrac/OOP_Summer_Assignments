#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QLayout>

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
    QLabel* label;
    QLineEdit* input;
    QListWidget* listDisplay;

private slots:
    void listAppend();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
