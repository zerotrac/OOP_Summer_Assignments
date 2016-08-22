//
//  Rectangle.h
//  HW1-P2
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle: public Shape
{
private:
    double height;
    double width;
    
public:
    Rectangle(double _height, double _width);
    virtual ~Rectangle();
    
public:
    virtual double getarea();
};

#endif
