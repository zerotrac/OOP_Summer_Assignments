//
//  Square.h
//  HW1-P2
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#ifndef SQUARE_H
#define SQUARE_H

#include "Shape.h"

class Square: public Shape
{
private:
    double side;
    
public:
    Square(double _side);
    virtual ~Square();
    
public:
    virtual double getarea();
};

#endif
