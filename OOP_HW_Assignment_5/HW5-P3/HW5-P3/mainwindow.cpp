#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widget = new QWidget();
    this->setCentralWidget(widget);

    size = 5;
    pics = new QPixmap*[size];
    for (int i = 0; i < size; ++i)
    {
        QString path = "Resources/" + QString::number(i + 1) + ".jpg";
        pics[i] = new QPixmap(path);
    }
    cur = 0;
    button = new QPushButton(widget);

    button->setIcon(*pics[0]);
    button->setFixedSize(QSize(pics[0]->width(), pics[0]->height()));
    button->setIconSize(QSize(pics[0]->width(), pics[0]->height()));
    button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    left = new QPushButton(widget);
    left->setText("<");
    right = new QPushButton(widget);
    right->setText(">");

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(left);
    layout->addWidget(button, 2);
    layout->addWidget(right);
    widget->setLayout(layout);

    QObject::connect(left, SIGNAL(clicked(bool)), this, SLOT(picDecrement()));
    QObject::connect(right, SIGNAL(clicked(bool)), this, SLOT(picIncrement()));
    QObject::connect(button, SIGNAL(clicked(bool)), this, SLOT(picIncrement()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::picIncrement()
{
    ++cur;
    if (cur == size) cur = 0;
    button->setIcon(*pics[cur]);
}

void MainWindow::picDecrement()
{
    --cur;
    if (cur == -1) cur = size - 1;
    button->setIcon(*pics[cur]);
}
