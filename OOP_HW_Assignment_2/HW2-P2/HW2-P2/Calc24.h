//
//  Calc24.h
//  HW2-P2
//
//  Created by 陈书新 on 16/8/23.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#ifndef CALC24_H
#define CALC24_H

#include <iostream>

class Calc24
{
private:
    long long* nums;
    int size;
    int opInBinary; // store the method to combine result in binary mode
    long long givenValue;
    long long result; // store the result closest to givenValue;
    
public:
    Calc24();
    ~Calc24();
    
public:
    void init(); // we assume that all the input integers are larger than 0
    void execute();
    void outit() const;
    
private:
};

#endif
