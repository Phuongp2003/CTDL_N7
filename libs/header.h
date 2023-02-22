#pragma once

#include "mylib.h"
#include <conio.h>
#include <dos.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

// Hằng số ----------------------------------------------------------------

#define MAXMB 300
#define MAXVe 100
// #define string std::string
#define ENTER 13

// struct -----------------------------------------------------------------

// ngày tháng
struct Date;
// Hành khách
class HanhKhach;
class Node; // @brief Node hành khách
// Máy bay
class MAYBAY;
// Chuyến bay
class ChuyenBay;
class NODE_ChuyenBay;
class VeMayBay;

// function ---------------------------------------------------------------

// Xử lý xâu

template <class T>
T InputXau(T &xau)
{
    char tmp[40];
    int i = 0;
    while ((tmp[i] = getch()) != ENTER)
    {
        if ((tmp[i] >= '0' && tmp[i] <= '9') ||
            (tmp[i] >= 'a' && tmp[i] <= 'z') ||
            (tmp[i] >= 'A' && tmp[i] <= 'Z') ||
            (tmp[i] == ' '))
        {
            std::cout << tmp[i];
            i++;
        }
        else if (tmp[i] == 8 && i >= 0)
        {
            int x_tmp = wherex(), y_tmp = wherey();
            gotoxy(x_tmp - 1, y_tmp);
            std::cout << " ";
            gotoxy(x_tmp - 1, y_tmp);
            i--;
        }
    }
    tmp[i] = '\0';
    return tmp;
}
