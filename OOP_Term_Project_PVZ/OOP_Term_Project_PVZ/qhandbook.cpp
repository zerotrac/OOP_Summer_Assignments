#include "qhandbook.h"
#include "ui_qhandbook.h"

QHandbook::QHandbook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QHandbook)
{
    ui->setupUi(this);

    this->setFocusPolicy(Qt::StrongFocus);
    this->setAutoFillBackground(true);
    this->setMouseTracking(true);
    QPalette palette;
    QPixmap backgroundBig("Resources/interface/day_background.jpg");
    QPixmap backgroundSmall = backgroundBig.copy(120, 0, 900, 600);
    palette.setBrush(QPalette::Background, QBrush(backgroundSmall));
    this->setPalette(palette);

    for (int i = 0; i < 15; ++i)
    {
        QMovie* mov = new QMovie("Resources/handbook/" + QString::number(i) + ".gif");
        mov->start();
        if (i == 7) mov->setSpeed(200);
        QRect rect = mov->frameRect();
        pics[i] = new QLabel(this);
        pics[i]->setMouseTracking(true);
        pics[i]->setFixedSize(rect.size());
        pics[i]->setMovie(mov);

        if (i < 9)
        {
            pics[i]->setGeometry(140 + i * 80, 170 - rect.height(), 0, 0);
        }
        else if (i < 12)
        {
            pics[i]->setGeometry(140 + (i - 9) * 80, 265 - rect.height(), 0, 0);
        }
        else
        {
            pics[i]->setGeometry(140 + (i - 12) * 80, 360 - rect.height(), 0, 0);
        }
    }
}

QHandbook::~QHandbook()
{
    delete ui;
}

void QHandbook::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = event->pos();
    qDebug() << "point = " << p.x() << p.y();
}

void QHandbook::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        emit signalWidget("main");
    }
}
