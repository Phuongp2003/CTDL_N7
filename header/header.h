#pragma once

// #include "mylib.h"
#include "raylib.h"
#include "raymath.h"
#include <conio.h>
#include <ctime>
#include <dos.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

// Hằng số ----------------------------------------------------------------

#define MAXMB 300
#define MAXVe 100
#define ENTER 13

// class -----------------------------------------------------------------

// ngày tháng
class Date;
// Hành khách
class HanhKhach;
class NodeHK;
class DSHankHach;

// Máy bay
class MayBay;
class DSMB;

// Chuyến bay
class ChuyenBay;
class NodeCB;
class DanhSachCB;

// Vé máy bay
class VeMayBay;
class DSVeMayBay;

// Định nghĩa function ở file header của các file

// Các hàm xử lí nhỏ
char *intTochar(int value, int size); // done
float per1000(int number);            // done
bool isGotStr(string _string, string _keyword);