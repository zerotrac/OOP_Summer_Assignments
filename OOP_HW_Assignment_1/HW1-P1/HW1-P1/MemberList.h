//
//  MemberList.h
//  OOP_HW_Assignment_1
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#ifndef MEMBERLIST_H
#define MEMBERLIST_H

#include <map>
#include <string>
#include "Member.h"

class MemberList
{
private:
    std::map<std::string, int> members;
    int size;

public:
    MemberList(Member* mbs, int size);
    ~MemberList();
    
    std::string operator [] (const std::string &name);
};

#endif
