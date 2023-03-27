#pragma once

// #include "mylib.h"
#include "raylib.h"
#include "raymath.h"
#include <conio.h>
#include <ctime>
#include <dos.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using std::string;
using std::cout;
using std::endl;

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