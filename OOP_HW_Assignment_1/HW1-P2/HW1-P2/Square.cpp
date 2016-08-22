//
//  Square.cpp
//  HW1-P2
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#include "Square.h"

Square::Square(double _side)
{
    side = _side;
}

Square::~Square()
{
    
}

double Square::getarea()
{
    return side * side;
}