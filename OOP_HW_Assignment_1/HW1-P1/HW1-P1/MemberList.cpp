//
//  MemberList.cpp
//  OOP_HW_Assignment_1
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#include "MemberList.h"

MemberList::MemberList(Member* mbs, int size)
{
    for (int i = 0; i < size; ++i)
    {
        members[mbs[i].getName()] = mbs[i].getAge();
    }
}

MemberList::~MemberList()
{
    
}

std::string MemberList::operator [] (const std::string &name)
{
    auto iter = members.find(name);
    if (iter == members.end())
    {
        return "No Found!";
    }
    else
    {
        int age = iter->second;
        std::string ret = "";
        while (age)
        {
            ret = static_cast<char>(age % 10 + 48) + ret;
            age /= 10;
        }
        return ret;
    }
}