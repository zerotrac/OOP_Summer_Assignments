#ifndef QINITIALINTERFACE_H
#define QINITIALINTERFACE_H

#include <QWidget>
#include <QPalette>
#include <QPushButton>
#include <QPixmap>
#include <QBitmap>
#include <QMessageBox>

namespace Ui {
class QInitialInterface;
}

class QInitialInterface : public QWidget
{
    Q_OBJECT

public:
    explicit QInitialInterface(QWidget *parent = 0);
    ~QInitialInterface();

private:
    static const int CLICK_DELTA = 2;

private:
    QPushButton* buttonAdventure;
    QPushButton* buttonWisdom;
    QPushButton* buttonMini;
    QPushButton* buttonOptions;
    QPushButton* buttonHelp;
    QPushButton* buttonQuit;

    QMessageBox* msgboxOptions;
    QMessageBox* msgboxHelp;
    QMessageBox* msgboxQuit;

private:
    void makeConnections();
    QString toStyleSheet(QString s);

signals:
    void signalWidget(QString);

private slots:
    void slotPressA();
    void slotPressW();
    void slotPressM();
    void slotReleaseA();
    void slotReleaseW();
    void slotReleaseM();
    void slotQuit();
    void slotAdventure();
    void slotMini();

private:
    Ui::QInitialInterface *ui;
};

#endif // QINITIALINTERFACE_H
