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

    QPixmap down("Resources/interface/card_down.png");
    down = down.scaled(600, 135);
    labelDown = new QLabel(this);
    labelDown->setFixedSize(down.size());
    labelDown->setGeometry((WINDOW_WIDTH - down.width()) / 2, WINDOW_HEIGHT - down.height(), 0, 0);
    labelDown->setPixmap(down);

    des0 = new QLabel(this);
    des0->setFixedSize(down.width() - 100, down.height());
    des0->setGeometry((WINDOW_WIDTH - down.width() + 100) / 2, WINDOW_HEIGHT - down.height(), 0, 0);
    QFont font;
    font.setPointSize(16);
    des0->setFont(font);

    for (int i = 0; i < 15; ++i)
    {
        des[i] = QString("<html><head/><body>");
    }
    des[0].append(package("这是向日葵，它能够生产建造植物的阳光。"));
    des[0].append(package("一定要把它放在后排，否则很容易被僵尸吃掉。"));

    des[1].append(package("这是豌豆射手，最普通的植物了。"));
    des[1].append(package("它的射程很远，每次射出一颗豌豆攻击同行的僵尸。"));

    des[2].append(package("这是寒冰射手，它的冰豌豆能让僵尸减速。"));
    des[2].append(package("减速时僵尸会减少50%的移动速度和攻击速度。"));

    des[3].append(package("这是双发射手，它每次能射出两颗豌豆。"));
    des[3].append(package("所以你现在知道它为什么比豌豆射手贵一倍了吧。"));

    des[4].append(package("这是机枪射手，它每次能射出四颗豌豆。"));
    des[4].append(package("但它的价格不是豌豆射手的四倍，因为它的机枪装置需要额外的阳光。"));

    des[5].append(package("这是坚果墙，它能抵挡僵尸造成的伤害。"));
    des[5].append(package("但它不能攻击，这真是美中不足的一点。"));

    des[6].append(package("这是土豆雷，它在一定的准备时间后会炸死踩到的僵尸。"));
    des[6].append(package("爆炸结束之后你就多了大量的土豆泥，加豌豆和鸡汁会非常美味。"));

    des[7].append(package("这是食人花，但他不吃人，只吃僵尸。"));
    des[7].append(package("它的肠胃功能不太好，所以消化一只僵尸需要比较长的时间。"));

    des[8].append(package("这是高坚果，它是坚果墙的好朋友。"));
    des[8].append(package("它能抵挡的伤害是坚果墙的两倍，但是它太高了。"));

    des[9].append(package("这是小喷菇，它能帮助你挺过早期僵尸的进攻。"));
    des[9].append(package("它不需要阳光就能种植，伤害和豌豆射手一样，但是射程没那么远。"));

    des[10].append(package("这是胆小菇，它非常怕僵尸。"));
    des[10].append(package("所以你必须把它种在后排，不然它会吓得躲进地里。"));

    des[11].append(package("这是寒冰菇，它可以完全冻住僵尸，冰冻结束后还能让僵尸减速。"));
    des[11].append(package("你可以视作它给了每个僵尸一闷棍，再喂了一颗冰豌豆。"));

    des[12].append(package("这是火爆辣椒，据说它的辣度是朝天椒的10000倍。"));
    des[12].append(package("它能烧死一整行的僵尸，但奇怪的是你的植物似乎防火。"));

    des[13].append(package("这是火炬树桩，它能使得经过的普通豌豆变成火焰形态，伤害加倍。"));
    des[13].append(package("但可惜的是，冰豌豆经过会变成普通豌豆，失去减速效果。"));

    des[14].append(package("这是樱桃炸弹，它没有不是炸弹的樱桃那么好吃。"));
    des[14].append(package("它能炸死周围的所有僵尸，真是暴力啊。"));

    for (int i = 0; i < 15; ++i)
    {
        des[i].append("</body></html>");
    }
}

QHandbook::~QHandbook()
{
    delete ui;
}

void QHandbook::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = event->pos();
    for (int i = 0; i < 15; ++i)
    {
        if (p.x() >= pics[i]->x() && p.x() <= pics[i]->x() + pics[i]->width() && p.y() >= pics[i]->y() && p.y() <= pics[i]->y() + pics[i]->height())
        {
            des0->setText(des[i]);
        }
    }
}

void QHandbook::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        emit signalWidget("main");
    }
}

QString QHandbook::package(QString st)
{
    return QString("<p><span style="" color:#ffffff;"">") + st + QString("</span></p>");
}

void QHandbook::gamePreparation()
{
    des0->clear();
}
