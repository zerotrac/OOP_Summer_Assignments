//
//  Member.cpp
//  OOP_HW_Assignment_1
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#include "Member.h"

Member::Member() : name("?"), age(0)
{
    
}

Member::Member(std::string _name, int _age) : name(_name), age(_age)
{
    
}

Member::~Member()
{
    
}

std::ostream& operator << (std::ostream& out, const Member& member)
{
    out << "Member Name: " << member.name << " Age: " << member.age;
    return out;
}