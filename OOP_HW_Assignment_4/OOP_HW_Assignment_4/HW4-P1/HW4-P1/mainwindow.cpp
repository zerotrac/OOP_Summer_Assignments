#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(300, 250));
    widget = new QWidget();
    widget->setFixedSize(QSize(300, 250));

    helpmsg = new QMessageBox(widget);
    helpmsg->setWindowTitle("Help");
    helpmsg->setText("\n用数字键输入数字，用AC键将数字清零。\n最多支持10位数字，超出过操作将会无效。");
    helpmsg->setIcon(QMessageBox::Information);
    helpmsg->setStandardButtons(QMessageBox::Ok);

    layout = new QGridLayout();
    mapper = new QSignalMapper();
    value = QString("");

    lcdnumber = new QLCDNumber(widget);
    lcdnumber->setFrameStyle(QFrame::Plain);
    lcdnumber->setSegmentStyle(QLCDNumber::Flat);
    lcdnumber->setDigitCount(10);
    lcdnumber->display("0");
    layout->addWidget(lcdnumber, 0, 0, 2, 3);

    buttons = new QPushButton*[12];
    for (int i = 0; i < 12; ++i)
    {
        buttons[i] = new QPushButton(widget);
        int num = i + 1 + (1 - i / 3) * 6;
        if (i == 10) ++num;
        if (i < 9 || i == 10)
        {
            buttons[i]->setText(QString::number(num, 10));
            QObject::connect(buttons[i], SIGNAL(clicked()), mapper, SLOT(map()));
            mapper->setMapping(buttons[i], num);
        }
        else if (i == 9)
        {
            buttons[i]->setText("Help");
            QObject::connect(buttons[i], SIGNAL(clicked()), this, SLOT(showHelpDialog()));
        }
        else
        {
            buttons[i]->setText("AC");
            QObject::connect(buttons[i], SIGNAL(clicked()), this, SLOT(lcdClear()));
        }
        int r = i / 3 + 2;
        int c = i % 3;
        layout->addWidget(buttons[i], r, c);
    }

    QObject::connect(mapper, SIGNAL(mapped(int)), this, SLOT(lcdAppend(int)));
    widget->setLayout(layout);
    this->setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lcdAppend(int digit)
{
    if (value.length() > 9) return;
    value.append(QString::number(digit));
    lcdnumber->display(value);
}

void MainWindow::lcdClear()
{
    value.clear();
    lcdnumber->display("0");
}

void MainWindow::showHelpDialog()
{
    helpmsg->show();
}
