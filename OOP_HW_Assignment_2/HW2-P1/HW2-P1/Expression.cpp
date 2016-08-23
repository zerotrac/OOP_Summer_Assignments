//
//  Expression.cpp
//  HW2-P1
//
//  Created by 陈书新 on 16/8/23.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#include "Expression.h"

Expression::Expression()
{
    
}

Expression::Expression(double _value, std::string _expr, bool _isSimple)
{
    value = _value;
    expr = _expr;
    isSimple = _isSimple;
}

Expression::~Expression()
{
    
}