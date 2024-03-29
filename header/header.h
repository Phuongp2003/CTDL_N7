#pragma once

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
using std::ios;
using std::ofstream;
using std::stoi;
using std::string;
using std::stringstream;

// Hằng số ----------------------------------------------------------------

#define MAXMB 300
#define MAXVe 100

enum ChuyenBayStatus
{
    HuyChuyen,
    ConVe,
    HetVe,
    HoanTat
};
enum InputTextboxMode
{
    ASCII2 = 1,
    Alphanumeric,
    UpperAlphanumeric,
    Alphalete,
    AlphaleteWithSpace,
    Numeric,
    Day,
    Month,
    Year,
    Hour,
    Minute
};

enum TextboxMode
{
    AntiLeak = 1,
    Auto
};

// Kích thước cửa sổ mặc định
#define WINDOW_WIDTH 1530
#define WINDOW_HEIGHT 820

// kích thước màn hình làm việc mặc định
#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 750

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
inline int pathBugLv = 0;

const string fontPath[2] = {"src/font/arial.ttf",
                            "../src/font/arial.ttf"},
             logoPath[2] = {"src/img/Logo_PTIT_University.png",
                            "../src/img/Logo_PTIT_University.png"},
             homeIconPath[2] = {"src/img/house_icon.png",
                                "../src/img/house_icon.png"},
             arrowLeftPath[2] = {"src/img/arrow_left.png",
                                 "../src/img/arrow_left.png"},
             status_TickPath[2] = {"src/img/status_tick.png",
                                   "../src/img/status_tick.png"},
             status_GreenPath[2] = {"src/img/status_green.png",
                                    "../src/img/status_green.png"},
             status_GrayPath[2] = {"src/img/status_gray.png",
                                   "../src/img/status_gray.png"},
             status_YellowPath[2] = {"src/img/status_yellow.png",
                                     "../src/img/status_yellow.png"},
             dataCBPath[2] = {"data/dataCB.txt",
                              "../data/dataCB.txt"},
             dataMBPath[2] = {"data/dataMB.txt",
                              "../data/dataMB.txt"},
             dataHKPath[2] = {"data/dataHK.txt",
                              "../data/dataHK.txt"};

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

class Queue;

// Định nghĩa function ở file header của các file

// Các hàm xử lí nhỏ
char *intToChar(int value, int size); // done
float per1000(int number);            // done
bool isGotStr(string _string, string _keyword);
int getCharSize(const char *_char);
int chuanHoaKey(int key, const char *str, int index_pos, int mode);
const char *strToChar(string str);
void Selection_Sort(int A[], int n);
void swap(int &a, int &b);
string intToString(int num, int size);
string charToString(const char *ch);
string trim(string str);

/// @brief Xóa toàn bộ khoảng trắng và chuyển thành chữ thường
/// @param str Chuỗi cần chuẩn hóa
void formatStr(string &str);

bool laNamNhuan(int nInput);

bool check_init(string path);
void debug_path();
