//
//  main.cpp
//  HW2-P2
//
//  Created by 陈书新 on 16/8/23.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#include <iostream>
#include "Calc24.h"

int main()
{
    Calc24* calc24 = new Calc24();
    calc24->init();
    calc24->execute();
    calc24->outit();
    delete calc24;
    
    return 0;
}
