//
//  Member.h
//  OOP_HW_Assignment_1
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <iostream>

class Member
{
private:
    const std::string name;
    const int age;

public:
    Member();
    Member(std::string _name, int _age);
    ~Member();
    
public:
    std::string getName() {return name;}
    int getAge() {return age;}
    
    friend std::ostream& operator << (std::ostream& out, const Member& member);
};

#endif
