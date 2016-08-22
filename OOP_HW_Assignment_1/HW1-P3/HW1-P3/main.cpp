//
//  main.cpp
//  HW1-P3
//
//  Created by 陈书新 on 16/8/22.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#include <iostream>
#include <string>

template<class T> T Max(const T& a, const T& b)
{
    if (a > b) return a;
    return b;
}

int main()
{
    int i = 1;
    int j = 2;
    std::cout << "Max(i, j): " << Max(i, j) << std::endl;
    double f1 = 11.1;
    double f2 = 22.2;
    std::cout << "Max(f1, f2): " << Max(f1, f2) << std::endl;
    std::string s1 = "AAAAA";
    std::string s2 = "BBBBB";
    std::cout << "Max(s1, s2): " << Max(s1, s2) << std::endl;
    return 0;
}
