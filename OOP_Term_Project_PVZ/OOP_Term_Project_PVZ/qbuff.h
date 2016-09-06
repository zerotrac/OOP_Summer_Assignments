#ifndef QBUFF_H
#define QBUFF_H

class QBuff
{
public:
    QBuff(int _f, int _s);
    ~QBuff();

public:
    int freezeDebuff;
    int stunDebuff;
};

#endif // QBUFF_H
