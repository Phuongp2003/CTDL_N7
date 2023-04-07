#pragma once
#include "header.h"
class Date
{
private:
    int Phut;
    int Gio;
    int Ngay;
    int Thang;
    int Nam;

public:
    Date();
    Date(int, int, int, int, int);
    void setGio(int);
    int getGio();
    void setPhut(int);
    int getPhut();
    void setNgay(int);
    int getNgay();
    void setThang(int);
    int getThang();
    void setNam(int);
    int getNam();
    void showTG();
    bool checkNgay();
    bool checkGio();
    bool checkNgayNhapVoiNgayHT();
    bool checkGioNhapVoiGioHT();
    bool checkDateHour();
    string PrintDateHour();
    string PrintDate();
    string PrintHour();
};
// dd/mm/yyyy hh:mm
// function
string intToString(int num,int size);
bool laNamNhuan(int nInput);//
