#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedHeight(100);

    widget = new QWidget(this);
    this->setCentralWidget(widget);

    QHBoxLayout* lineLayout = new QHBoxLayout();
    QString date = QString("现在是  2016 年  08 月  26 日");
    QStringList dateList = date.split("  ");
    std::cout << "size = " << dateList.size() << std::endl;
    labels = new QLabel*[4];
    for (int i = 0; i < 4; ++i)
    {
        std::cout << "i = " << i << std::endl;
        labels[i] = new QLabel(widget);
        labels[i]->setText(dateList.at(i));
        lineLayout->addWidget(labels[i]);
    }
    widget->setLayout(lineLayout);

    menubar = new QMenuBar(this);
    this->setMenuBar(menubar);
    QMenu* editMenu = menubar->addMenu("&Edit");
    QAction* modifyAction = new QAction(editMenu);
    editMenu->addAction(modifyAction);
    modifyAction->setText("&Modify...");

    dialog = new QDialog(widget);
    dialog->setWindowTitle("Modify");
    dialog->setModal(true);
    QLabel* dialogLabel = new QLabel(dialog);
    dialogLabel->setText("请更改日期：");
    dialogDate = new QDateEdit(dialog);
    dialogDate->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    dialogDate->setDisplayFormat("yyyy.MM.dd");
    QHBoxLayout* HL1 = new QHBoxLayout();
    HL1->addWidget(dialogLabel);
    HL1->addWidget(dialogDate);
    QPushButton* ok = new QPushButton(dialog);
    ok->setText("Ok");
    QPushButton* cancel = new QPushButton(dialog);
    cancel->setText("Cancel");
    QHBoxLayout* HL2 = new QHBoxLayout();
    HL2->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
    HL2->addWidget(ok);
    HL2->addWidget(cancel);
    QVBoxLayout* HL3 = new QVBoxLayout();
    HL3->addLayout(HL1);
    HL3->addLayout(HL2);
    dialog->setLayout(HL3);

    msgbox = new QMessageBox(dialog);
    msgbox->addButton(QMessageBox::Ok);
    msgbox->setIcon(QMessageBox::Information);
    msgbox->setText("\n修改成功！");

    QObject::connect(modifyAction, SIGNAL(triggered(bool)), this, SLOT(dialogShow()));
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(modifyDate()));
    QObject::connect(cancel, SIGNAL(clicked()), dialog, SLOT(close()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dialogShow()
{
    dialog->show();
}

void MainWindow::modifyDate()
{
    msgbox->show();
    if (msgbox->exec() == QMessageBox::Ok)
    {
        QString year = dialogDate->sectionText(dialogDate->sectionAt(0));
        QString month = dialogDate->sectionText(dialogDate->sectionAt(1));
        QString day = dialogDate->sectionText(dialogDate->sectionAt(2));
        labels[1]->setText(year + " 年");
        labels[2]->setText(month + " 月");
        labels[3]->setText(day + " 日");
    }
    dialog->close();
}
