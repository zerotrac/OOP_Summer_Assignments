//
//  Calc24.h
//  HW2-P1
//
//  Created by 陈书新 on 16/8/23.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#ifndef CALC24_H
#define CALC24_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Expression.h"

class Calc24
{
private:
    int nums[4];
    std::vector<std::string> results;
    
public:
    Calc24();
    ~Calc24();

public:
    void init();
    void execute();
    void outit() const;
    
private:
    std::string myItoa(int x) const;
    void findResults(int restNums, Expression* expressions);
};

#endif
