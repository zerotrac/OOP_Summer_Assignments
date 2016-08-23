//
//  Calc24.cpp
//  HW2-P1
//
//  Created by 陈书新 on 16/8/23.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#include "Calc24.h"

Calc24::Calc24()
{
    for (int i = 0; i < 3; ++i)
    {
        nums[i] = 0;
    }
    results.clear();
}

Calc24::~Calc24()
{
    
}

void Calc24::init()
{
    for (int i = 0; i < 4; ++i)
    {
        std::cin >> nums[i];
    }
}

void Calc24::execute()
{
    Expression* expressions = new Expression[4];
    for (int i = 0; i < 4; ++i)
    {
        expressions[i] = Expression(nums[i], myItoa(static_cast<int>(nums[i])), true);
    }
    findResults(4, expressions);
    delete[] expressions;
    
    std::sort(results.begin(), results.end());
    auto tail = std::unique(results.begin(), results.end());
    results.erase(tail, results.end());
}

void Calc24::outit() const
{
    if (results.empty())
    {
        std::cout << "no" << std::endl;
        return;
    }
    std::cout << "Total Methods Count = " << results.size() << std::endl;
    for (std::string result: results)
    {
        std::cout << result << std::endl;
    }
}

std::string Calc24::myItoa(int x) const
{
    if (x == 0) return "0";
    
    std::string ret = "";
    while (x)
    {
        ret = static_cast<char>(x % 10 + 48) + ret;
        x /= 10;
    }
    return ret;
}

void Calc24::findResults(int restNums, Expression* expressions)
{
    if (restNums == 1)
    {
        if (std::fabs(expressions[0].value - 24) < 1e-6)
        {
            results.push_back(expressions[0].expr);
        }
        return;
    }
    
    Expression* nextstep = new Expression[4];
    for (int i = 0; i < restNums; ++i)
    {
        for (int j = 0; j < restNums; ++j)
        {
            if (i != j && (std::fabs(expressions[i].value - expressions[j].value) > 1e-6 || i < j))
            {
                for (int op = 0; op < 4; ++op)
                {
                    // op = 0, 1, 2, 3 refers to +, -, *, /
                    double dummy;
                    std::string st;
                    if (op == 0)
                    {
                        dummy = expressions[i].value + expressions[j].value;
                        st = "+";
                    }
                    else if (op == 1)
                    {
                        dummy = expressions[i].value - expressions[j].value;
                        st = "-";
                    }
                    else if (op == 2)
                    {
                        dummy = expressions[i].value * expressions[j].value;
                        st = "*";
                    }
                    else if (op == 3)
                    {
                        if (std::fabs(expressions[j].value) < 1e-6) continue;
                        dummy = expressions[i].value / expressions[j].value;
                        st = "/";
                    }
                    if (expressions[i].isSimple)
                    {
                        st = expressions[i].expr + st;
                    }
                    else
                    {
                        st = "(" + expressions[i].expr + ")" + st;
                    }
                    if (expressions[j].isSimple)
                    {
                        st = st + expressions[j].expr;
                    }
                    else
                    {
                        st = st + "(" + expressions[j].expr + ")";
                    }
                    
                    nextstep[0] = Expression(dummy, st, false);
                    int nsCount = 0;
                    for (int k = 0; k < restNums; ++k)
                    {
                        if (k != i && k != j)
                        {
                            nextstep[++nsCount] = expressions[k];
                        }
                    }
                    findResults(restNums - 1, nextstep);
                }
            }
        }
    }
}
