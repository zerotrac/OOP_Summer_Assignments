//
//  main.cpp
//  HW3-P1
//
//  Created by 陈书新 on 16/8/24.
//  Copyright © 2016年 陈书新. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <algorithm>

void initializeArray(int***& a, int N)
{
    a = new int**[N];
    for (int i = 0; i < N; ++i)
    {
        a[i] = new int*[N];
        for (int j = 0; j < N; ++j)
        {
            a[i][j] = new int[N];
            for (int k = 0; k < N; ++k)
            {
                a[i][j][k] = rand() % 1000; // generate the value of arrays randomly
            }
        }
    }
}

void deleteArray(int***& a, int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            delete[] a[i][j];
        }
        delete[] a[i];
    }
    delete[] a;
}

void checkPermutation(int* a, int way)
{
    if (way < 2)
    {
        a[0] = 0;
        a[1] = 1;
        a[2] = 2;
    }
    else if (way < 4)
    {
        a[0] = 1;
        a[1] = 0;
        a[2] = 2;
    }
    else
    {
        a[0] = 2;
        a[1] = 0;
        a[2] = 1;
    }
    
    if (way & 1) std::swap(a[1], a[2]);
}

void checkTime(int N, int M)
{
    int*** a;
    int*** b;
    int*** c;
    initializeArray(a, N); // allocate memory for arrays dynamically
    initializeArray(b, N);
    initializeArray(c, N);
    // there are 6 different ways to loop throught the array
    // we use ways = 0, 1, 2, 3, 4, 5 to represent ijk, ikj, jik, jki, kij, kji
    int p[3];
    int i[3];
    std::cout << std::fixed << std::setprecision(3);
    for (int way = 0; way < 6; ++way)
    {
        checkPermutation(p, way); // i[] stores the order of the three loop variables
        
        auto startTime = clock();
        for (int rep = 0; rep < M; ++rep)
        {
            for (i[p[0]] = 0; i[p[0]] < N; ++i[p[0]])
            {
                for (i[p[1]] = 0; i[p[1]] < N; ++i[p[1]])
                {
                    for (i[p[2]] = 0; i[p[2]] < N; ++i[p[2]])
                    {
                        c[i[0]][i[1]][i[2]] = a[i[0]][i[1]][i[2]] + b[i[0]][i[1]][i[2]];
                    }
                }
            }
        }
        auto finishTime = clock();
        double runningTime = static_cast<double>(finishTime - startTime) / CLOCKS_PER_SEC;
        std::cout << "way = " << way << " running time = " << runningTime << "s average time = " << runningTime / M << "s" << std::endl;
    }
    
    deleteArray(a, N); // do not forget to release the memory
    deleteArray(b, N);
    deleteArray(c, N);
}

int main(int argc, const char* argv[])
{
    srand(static_cast<unsigned int>(time(0)));
    if (argc != 3)
    {
        std::cout << "Arguments Error!" << std::endl;
        return 0;
    }
    
    // N represents the size of arrays
    int N = atoi(argv[1]);
    // M represents the repititions times in order to enlarge the time difference
    int M = atoi(argv[2]);
    checkTime(N, M);
    return 0;
}

