//
//  Circle.h
//  HW1-P2
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle: public Shape
{
private:
    static double pi;
    
private:
    double radius;
    
public:
    Circle(double _radius);
    virtual ~Circle();

public:
    virtual double getarea();
};

#endif
