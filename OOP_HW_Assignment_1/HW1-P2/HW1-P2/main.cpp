//
//  main.cpp
//  HW1-P2
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#include <iostream>
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"

int main()
{
    Shape * shapes[4];
    Circle circle(2.0);
    Rectangle rectangle(3.0, 4.0);
    Square square1(5.0);
    Square square2(4.0);
    
    shapes[0] = &circle;
    shapes[1] = &rectangle;
    shapes[2] = &square1;
    shapes[3] = &square2;
    
    for (int k = 0; k < 4; ++k)
    {
        std::cout << "Area is " << shapes[k]->getarea() << std::endl;
    }
    return 0;
}
