#pragma once

// #include "mylib.h"
#include "raylib.h"
#include "raymath.h"

#include <array>
#include <conio.h>
#include <ctime>
#include <dos.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using std::array;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

// Hằng số ----------------------------------------------------------------

#define MAXMB 300
#define MAXVe 100
#define ENTER 13

const char idChu[26] = {
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
    'G',
    'H',
    'I',
    'J',
    'K',
    'L',
    'M',
    'N',
    'O',
    'P',
    'Q',
    'R',
    'S',
    'T',
    'U',
    'V',
    'W',
    'X',
    'Y',
    'Z',
};

const char idSo[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

// class -----------------------------------------------------------------

// ngày tháng
class Date;

// Hành khách
class HanhKhach;
class NodeHK;
class DsHanhKhach;

// Máy bay
class MayBay;
class DsMayBay;

// Vé máy bay
class VeMayBay;
class DsVeMayBay;

// Chuyến bay
class ChuyenBay;
class NodeCB;
class DsChuyenBay;

// Định nghĩa function ở file header của các file

// Các hàm xử lí nhỏ
char *intToChar(int value, int size); // done
float per1000(int number);            // done
bool isGotStr(string _string, string _keyword);
int getCharSize(const char *_char);
int chuanHoaKey(int key, const char *str, int index_pos, int mode);
int strcmp(const char *str1, const char *str2);
const char *strToChar(string str);