#pragma once
#include "chuyenbay.h"
#include "header.h"
#include <string>
#define MAXMB 300

#ifndef MAYBAY
#define MAYBAY

class MayBay
{
private:
    char SoHieuMB[16]; // @note xây dựng hàm chỉ cho phép nhập 16 kí tự
    char LoaiMB[41];   // 41 kí tự
    int SoDay;
    int SoDong;
    int SoLuotTHCB;

public:
    MayBay();
    MayBay(const char *SoHieuMB, const char *LoaiMB, int SoDay, int SoDong);
    void setSoHieuMB(const char *SoHieuMB);
    char *getSoHieuMB();
    void setLoaiMB(const char *LoaiMB);
    char *getLoaiMB();
    void setSoDay(int SoDay);
    int getSoDay();
    void setSoDong(int SoDong);
    int getSoDong();
    int getSoCho();
    void show_MB();
    bool Kiemtrasocho(int socho);
    void DSChoNgoi();
    void TangSLTHCB();
    int getSoLuotBay();
    
    MayBay* getMB();
    ~MayBay();
};

// MayBay *mb = new MayBay[300];

// typedef struct MAYBAY MB;
// struct listMB
// {
//     int n;
//     MAYBAY *nodes[MAXMB];
// };
// typedef struct listMB LISTMB;

// Danh sách con trỏ của máy bay
//======================================================================
class DSMB
{
private:
    int size = 0;
    MayBay *data[MAXMB];

public:
    DSMB();
    // void setsize(int size);
    int getsize();
    void getDSMB();
    bool Is_Empty(DSMB &DS);
    bool Is_Full(DSMB &DS);
    MayBay *New_MB(MayBay &maybay);
    void Insert_MB(DSMB &DS, MayBay &maybay);
    void Delete_MB(DSMB &DS, int index);
    int Find_MB(DSMB &DS, const char *SoHieuMB);
    void Delete_DSMB(DSMB &DS);
    MayBay* getMB(int index);
    ~DSMB();
};

#endif