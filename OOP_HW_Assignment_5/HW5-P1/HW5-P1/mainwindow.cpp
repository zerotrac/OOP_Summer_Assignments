#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widget = new QWidget(this);
    this->setCentralWidget(widget);

    QVBoxLayout* widgetLayout = new QVBoxLayout();
    QHBoxLayout* editLayout = new QHBoxLayout();
    label = new QLabel(widget);
    label->setText("Edit:");
    editLayout->addWidget(label);
    input = new QLineEdit(widget);
    editLayout->addWidget(input);
    widgetLayout->addLayout(editLayout);

    listDisplay = new QListWidget();
    widgetLayout->addWidget(listDisplay);
    widget->setLayout(widgetLayout);

    QObject::connect(input, SIGNAL(returnPressed()), this, SLOT(listAppend()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listAppend()
{
    listDisplay->addItem(input->text());
    listDisplay->setCurrentRow(listDisplay->count() - 1);
    input->clear();
}
