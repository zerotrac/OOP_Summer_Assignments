#ifndef PAIRELIMINATE_H
#define PAIRELIMINATE_H

#include <QWidget>

namespace Ui {
class PairEliminate;
}

class PairEliminate : public QWidget
{
    Q_OBJECT

public:
    explicit PairEliminate(QWidget *parent = 0);
    ~PairEliminate();

private:
    Ui::PairEliminate *ui;
};

#endif // PAIRELIMINATE_H
