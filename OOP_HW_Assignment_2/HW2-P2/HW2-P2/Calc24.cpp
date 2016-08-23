//
//  Calc24.cpp
//  HW2-P2
//
//  Created by 陈书新 on 16/8/23.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#include "Calc24.h"

Calc24::Calc24()
{
    result = -1;
}

Calc24::~Calc24()
{
    
}

void Calc24::init()
{
    std::cin >> size >> givenValue;
    nums = new long long[size];
    for (int i = 0; i < size; ++i)
    {
        std::cin >> nums[i];
    }
}

void Calc24::execute()
{
    int opMax = 1 << (size - 1);
    for (int i = 0; i < opMax; ++i)
    {
        long long curValue = nums[0];
        bool success = true;
        for (int j = 1; j < size; ++j)
        {
            if (i & (1 << (j - 1))) // do multiplication
            {
                if (curValue > LONG_LONG_MAX / nums[j])
                {
                    success = false;
                    break;
                }
                curValue *= nums[j];
            }
            else // do addition
            {
                if (curValue > LONG_LONG_MAX - nums[j])
                {
                    success = false;
                    break;
                }
                curValue += nums[j];
            }
        }
        if (success)
        {
            if (curValue >= givenValue && (result == -1 || curValue < result))
            {
                result = curValue;
                opInBinary = i;
            }
        }
    }
}

void Calc24::outit() const
{
    if (result != givenValue)
    {
        std::cout << "No" << std::endl;
        if (result != -1)
        {
            std::cout << result << std::endl;
        }
        else
        {
            std::cout << "Cannot find a result larger than the given value." << std::endl;
        }
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            std::cout << nums[i];
            if (i != size - 1)
            {
                if (opInBinary & (1 << i)) std::cout << "*"; else std::cout << "+";
            }
            else
            {
                std::cout << std::endl;
            }
        }
    }
}