#pragma once
#include "header.h"
#include <string>
#define MAXMB 300

class MayBay //@brief MayBay @note abc
{
private:
    char *SoHieuMB; // @note xây dựng hàm chỉ cho phép nhập 16 kí tự
    char *LoaiMB;   // @note
    int SoDay;
    int SoDong;

public:
    MayBay();
    MayBay(char *SoHieuMB, char *LoaiMB, int SoDay, int SoDong);
    void setSoHieuMB(char *SoHieuMB);
    char *getSoHieuMB();
    void setLoaiMB(char *LoaiMB);
    char *getLoaiMB();
    void setSoDay(int SoDay);
    int getSoDay();
    void setSoDong(int SoDong);
    int getSoDong();
    ~MayBay();
};
MayBay::MayBay() {}
MayBay::MayBay(char *SoHieuMB, char *LoaiMB, int SoDay, int SoDong)
{
    this->SoHieuMB = SoHieuMB;
    this->LoaiMB = LoaiMB;
    this->SoDay = SoDay;
    this->SoDong = SoDong;
}

void MayBay::setSoHieuMB(char *SoHieuMB)
{
    this->SoHieuMB = SoHieuMB;
}
char *MayBay::getSoHieuMB()
{
    return SoHieuMB;
}
void MayBay::setLoaiMB(char *LoaiMB)
{
    this->LoaiMB = LoaiMB;
}
char *MayBay::getLoaiMB()
{
    return LoaiMB;
}
void MayBay::setSoDay(int SoDay)
{
    this->SoDay = SoDay;
}
int MayBay::getSoDay()
{
    return SoDay;
}
void MayBay::setSoDong(int SoDong)
{
    this->SoDong = SoDong;
}
int MayBay::getSoDong()
{
    return SoDong;
}

// typedef struct MAYBAY MB;
// struct listMB
// {
//     int n;
//     MAYBAY *nodes[MAXMB];
// };
// typedef struct listMB LISTMB;

void nhap();