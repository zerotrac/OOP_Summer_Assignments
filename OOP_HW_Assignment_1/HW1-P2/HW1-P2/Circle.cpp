//
//  Circle.cpp
//  HW1-P2
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#include "Circle.h"

double Circle::pi = 3.1415926;

Circle::Circle(double _radius)
{
    radius = _radius;
}

Circle::~Circle()
{
    
}

double Circle::getarea()
{
    return pi * radius * radius;
}