#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Temperature Converter");
    this->setFixedSize(QSize(300, 200));
    widget = new QWidget();

    boxCel = new QGroupBox(widget);
    boxCel->setTitle("Celsius");
    dialCel = new QDial(boxCel);
    dialCel->setMinimum(-100);
    dialCel->setMaximum(100);
    dialCel->setValue(0);
    numberCel = new QLCDNumber(boxCel);
    numberCel->setFrameStyle(QFrame::Plain);
    numberCel->setSegmentStyle(QLCDNumber::Flat);
    numberCel->display(dialCel->value());
    QVBoxLayout* layoutForCel = new QVBoxLayout();
    layoutForCel->addWidget(dialCel);
    layoutForCel->addWidget(numberCel);
    boxCel->setLayout(layoutForCel);

    boxFeh = new QGroupBox(widget);
    boxFeh->setTitle("Fahrenheit");
    dialFeh = new QDial(boxFeh);
    dialFeh->setMinimum(-148);
    dialFeh->setMaximum(212);
    dialFeh->setValue(32);
    numberFeh = new QLCDNumber(boxFeh);
    numberFeh->setFrameStyle(QFrame::Plain);
    numberFeh->setSegmentStyle(QLCDNumber::Flat);
    numberFeh->display(dialFeh->value());
    QVBoxLayout* layoutForFeh = new QVBoxLayout();
    layoutForFeh->addWidget(dialFeh);
    layoutForFeh->addWidget(numberFeh);
    boxFeh->setLayout(layoutForFeh);

    QHBoxLayout* layoutForBox = new QHBoxLayout();
    layoutForBox->addWidget(boxCel);
    layoutForBox->addWidget(boxFeh);
    widget->setLayout(layoutForBox);

    this->setCentralWidget(widget);

    QObject::connect(dialCel, SIGNAL(valueChanged(int)), this, SLOT(adjustFeh(int)));
    QObject::connect(dialFeh, SIGNAL(valueChanged(int)), this, SLOT(adjustCel(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::adjustCel(int value)
{
    numberFeh->display(value);
    value = static_cast<int>((value - 32) / 1.8);
    if (value == dialCel->value()) return;
    dialCel->setValue(value);
    numberCel->display(value);
}

void MainWindow::adjustFeh(int value)
{
    numberCel->display(value);
    value = static_cast<int>(value * 1.8 + 32);
    if (value == dialFeh->value()) return;
    dialFeh->setValue(value);
    numberFeh->display(value);
}
