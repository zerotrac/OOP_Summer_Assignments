#include "qinitialinterface.h"
#include "ui_qinitialinterface.h"
#include <iostream>

QInitialInterface::QInitialInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QInitialInterface)
{
    ui->setupUi(this);

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap("Resources/interface/initial_interface_background.png")));
    this->setPalette(palette);

    buttonAdventure = new QPushButton(this);
    buttonAdventure->setFixedSize(QPixmap("Resources/interface/initial_interface_adventure.png").size());
    buttonAdventure->setMask(QPixmap("Resources/interface/initial_interface_adventure.png").mask());
    buttonAdventure->setIconSize(QPixmap("Resources/interface/initial_interface_adventure.png").size());
    buttonAdventure->setGeometry(508, 80, 0, 0);
    buttonAdventure->setStyleSheet(toStyleSheet("adventure"));

    buttonWisdom = new QPushButton(this);
    buttonWisdom->setFixedSize(QPixmap("Resources/interface/initial_interface_wisdom.png").size());
    buttonWisdom->setMask(QPixmap("Resources/interface/initial_interface_wisdom.png").mask());
    buttonWisdom->setGeometry(515, 210, 0, 0);
    buttonWisdom->setStyleSheet(toStyleSheet("wisdom"));

    buttonMini = new QPushButton(this);
    buttonMini->setFixedSize(QPixmap("Resources/interface/initial_interface_mini.png").size());
    buttonMini->setMask(QPixmap("Resources/interface/initial_interface_mini.png").mask());
    buttonMini->setGeometry(522, 315, 0, 0);
    buttonMini->setStyleSheet(toStyleSheet("mini"));


    buttonOptions = new QPushButton(this);
    buttonOptions->setFixedSize(QPixmap("Resources/interface/initial_interface_options.png").size());
    buttonOptions->setMask(QPixmap("Resources/interface/initial_interface_options.png").mask());
    buttonOptions->setGeometry(668, 488, 0, 0);
    buttonOptions->setStyleSheet(toStyleSheet("options"));

    buttonHelp = new QPushButton(this);
    buttonHelp->setFixedSize(QPixmap("Resources/interface/initial_interface_help.png").size());
    buttonHelp->setMask(QPixmap("Resources/interface/initial_interface_help.png").mask());
    buttonHelp->setGeometry(740, 520, 0, 0);
    buttonHelp->setStyleSheet(toStyleSheet("help"));

    buttonQuit = new QPushButton(this);
    buttonQuit->setFixedSize(QPixmap("Resources/interface/initial_interface_quit.png").size());
    buttonQuit->setMask(QPixmap("Resources/interface/initial_interface_quit.png").mask());
    buttonQuit->setGeometry(805, 505, 0, 0);
    buttonQuit->setStyleSheet(toStyleSheet("quit"));

    msgboxOptions = new QMessageBox(QMessageBox::Information, "", "默认开启开发者模式，所以不用在这里选择。\n使用键盘进行开发者的调试。\n1：产生5个普通僵尸；\n2：产生5个路障僵尸；\n3：产生5个铁桶僵尸；\nA：增加100阳光；\nC：将所有植物冷却时间重置；\nD：减少100阳光；\nH：显示/隐藏生命值条；\nJ：使用火爆辣椒清场。", QMessageBox::Ok, this);
    msgboxHelp = new QMessageBox(QMessageBox::Information, "", "没有帮助。\n编写者：zerotrac\n开源代码：https://github.com/zerotrac/OOP_Summer_Assignments/tree/master/OOP_Term_Project_PVZ/OOP_Term_Project_PVZ", QMessageBox::Ok, this);
    msgboxQuit = new QMessageBox(QMessageBox::Warning, "", "确认要退出植物大战僵尸吗？", QMessageBox::Ok | QMessageBox::Cancel, this);


    makeConnections();
}

QInitialInterface::~QInitialInterface()
{
    delete ui;
}

void QInitialInterface::makeConnections()
{

    QObject::connect(buttonAdventure, SIGNAL(pressed()), this, SLOT(slotPressA()));
    QObject::connect(buttonAdventure, SIGNAL(released()), this, SLOT(slotReleaseA()));
    QObject::connect(buttonAdventure, SIGNAL(clicked(bool)), this, SLOT(slotAdventure()));
    QObject::connect(buttonWisdom, SIGNAL(pressed()), this, SLOT(slotPressW()));
    QObject::connect(buttonWisdom, SIGNAL(released()), this, SLOT(slotReleaseW()));
    QObject::connect(buttonMini, SIGNAL(pressed()), this, SLOT(slotPressM()));
    QObject::connect(buttonMini, SIGNAL(released()), this, SLOT(slotReleaseM()));
    QObject::connect(buttonMini, SIGNAL(clicked(bool)), this, SLOT(slotMini()));

    QObject::connect(buttonOptions, SIGNAL(clicked(bool)), msgboxOptions, SLOT(show()));
    QObject::connect(buttonHelp, SIGNAL(clicked(bool)), msgboxHelp, SLOT(show()));
    QObject::connect(buttonQuit, SIGNAL(clicked(bool)), this, SLOT(slotQuit()));
}

QString QInitialInterface::toStyleSheet(QString s)
{
    QString p1 = "QPushButton {background-image: url(Resources/interface/initial_interface_" + s + ".png); border: none;}";
    QString p2 = "QPushButton:hover {background-image: url(Resources/interface/initial_interface_" + s + "_clicked.png); border: none;}";
    QString p3 = "QPushButton:pressed {background-image: url(Resources/interface/initial_interface_" + s + "_clicked.png); border: none;}";
    return p1 + p2 + p3;
}

void QInitialInterface::slotPressA()
{
    buttonAdventure->setGeometry(buttonAdventure->pos().x() + CLICK_DELTA, buttonAdventure->pos().y() + CLICK_DELTA, 0, 0);
}

void QInitialInterface::slotPressW()
{
    buttonWisdom->setGeometry(buttonWisdom->pos().x() + CLICK_DELTA, buttonWisdom->pos().y() + CLICK_DELTA, 0, 0);
}

void QInitialInterface::slotPressM()
{
    buttonMini->setGeometry(buttonMini->pos().x() + CLICK_DELTA, buttonMini->pos().y() + CLICK_DELTA, 0, 0);
}

void QInitialInterface::slotReleaseA()
{
    buttonAdventure->setGeometry(buttonAdventure->pos().x() - CLICK_DELTA, buttonAdventure->pos().y() - CLICK_DELTA, 0, 0);
}

void QInitialInterface::slotReleaseW()
{
    buttonWisdom->setGeometry(buttonWisdom->pos().x() - CLICK_DELTA, buttonWisdom->pos().y() - CLICK_DELTA, 0, 0);
}

void QInitialInterface::slotReleaseM()
{
    buttonMini->setGeometry(buttonMini->pos().x() - CLICK_DELTA, buttonMini->pos().y() - CLICK_DELTA, 0, 0);
}

void QInitialInterface::slotQuit()
{
    msgboxQuit->show();
    if (msgboxQuit->exec() == QMessageBox::Ok)
    {
        qApp->quit();
    }
    else
    {
        msgboxQuit->hide();
    }
}

void QInitialInterface::slotAdventure()
{
    emit signalWidget(QString("day"));
}

void QInitialInterface::slotMini()
{
    emit signalWidget(QString("eliminate"));
}
