#ifndef QHANDBOOK_H
#define QHANDBOOK_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>

namespace Ui {
class QHandbook;
}

class QHandbook : public QWidget
{
    Q_OBJECT

public:
    explicit QHandbook(QWidget *parent = 0);
    ~QHandbook();

private:
    QLabel* pics[15];

private:
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

signals:
    void signalWidget(QString);

private:
    Ui::QHandbook *ui;
};

#endif // QHANDBOOK_H
