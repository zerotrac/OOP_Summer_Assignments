//
//  main.cpp
//  OOP_HW_Assignment_1
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#include <iostream>
#include "Member.h"
#include "MemberList.h"

int main()
{
    Member newCommers[5] = {Member("Zhang San", 22),
        Member("Li Si", 19),
        Member("Wang Wu", 18),
        Member("Zhao Liu", 24)};
    
    for (int i = 0; i < 5; ++i)
    {
        std::cout << newCommers[i] << std::endl;
    }
    
    std::string name[5] = {"Zhang San", "Li Si", "Wang Wu", "Zhao Liu", "Pin Yin"};
    MemberList list(newCommers, 5);
    for (int i = 0; i < 5; i++)
    {
        std::cout << list[name[i]] << std::endl;
    }
    return 0;
}
