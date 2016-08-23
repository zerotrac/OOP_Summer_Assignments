//
//  Expression.h
//  HW2-P1
//
//  Created by 陈书新 on 16/8/23.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

class Expression // used in findResults() to store the value of an expression
{
public:
    double value;
    std::string expr;
    bool isSimple; // check if the expr is only a number or not
    
public:
    Expression();
    Expression(double _value, std::string _expr, bool _isSimple);
    ~Expression();
};

#endif
