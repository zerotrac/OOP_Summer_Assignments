//
//  Shape.h
//  HW1-P2
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#ifndef SHAPE_H
#define SHAPE_H

class Shape // virtual
{
public:
    Shape();
    virtual ~Shape();
    
public:
    virtual double getarea() = 0;
};

#endif
