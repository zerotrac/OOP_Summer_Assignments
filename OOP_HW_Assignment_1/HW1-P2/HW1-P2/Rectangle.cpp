//
//  Rectangle.cpp
//  HW1-P2
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#include "Rectangle.h"

Rectangle::Rectangle(double _height, double _width)
{
    height = _height;
    width = _width;
}

Rectangle::~Rectangle()
{
    
}

double Rectangle::getarea()
{
    return height * width;
}