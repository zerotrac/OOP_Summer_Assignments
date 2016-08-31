#ifndef QUNIT_H
#define QUNIT_H

#include <QObject>
#include <vector>
#include "qweapon.h"
#include "qmovie.h"
#include "const.h"

// 用std::set存储当前所有存活的单位的编号(id)
// 用std::vector存储所有存在过的单位指针
// 在需要遍历所有存活的单位的时候，扫一遍std::set即可

class QUnit : public QObject
{
    Q_OBJECT

public:
    explicit QUnit(QObject *parent = 0);
    virtual ~QUnit();

protected:
    int id; // 表示单位的编号

    // 下面所有的参数带base的表示基础参数值
    // 不带base的在每一帧自动变化，为计算buff和debuff之后的参数值

    int atk; // 攻击力
    int baseAtk;
    int hp; // 血量
    int baseHp;
    int cd; // 攻击冷却时间
    int baseCd;
    int rng; // 攻击距离
    int baserng;
    int bullet; // 武器装填数量，一般只有1和无限两种

    double spdX; // 移动速度，分x（水平）和y（垂直）方向
    double spdY;
    double baseSpdX;
    double baseSpdY;
    double posX; // 位置
    double posY;

    QWeapon* weapon; //弹道

protected:
    std::vector<QMovie*> pics; // 单位的动画
    int countPic;
    int currentPic;

public:
    virtual bool canAttack() = 0; // 该单位是否可以攻击，要考虑当前cd
    virtual std::vector<QWeapon*> attack() = 0; // 若可以攻击，返回一个弹道
    void move();
    virtual bool isPlant() = 0;
    virtual bool isZombie() = 0;
    bool isDead(); // hp为0或者bullet为0时死亡
    virtual void updateInfo() = 0; // 每一帧更新单位信息
};

#endif // QUNIT_H
