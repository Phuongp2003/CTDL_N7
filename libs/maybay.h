#pragma once
#include "header.h"

struct MayBay
{
    char SoHieuMB[15];
    char LoaiMB[40];
    int soDay;
    int soDong;
};

struct listMB
{
    int n;
    MayBay *nodes[MAXMB];
};
typedef struct listMB LISTMB;

struct Ve
{
    char ViTriNgoi[5];
    char CMND[11];
};