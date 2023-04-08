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
    Date(int _Ngay, int _Thang, int _Nam, int _Gio, int _Phut);
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
    bool checkNgayGio();
    string PrintDateHour();
    string PrintDate();
    string PrintHour();
    bool operator<(Date another);
    bool operator=(Date another);
};
// dd/mm/yyyy hh:mm
// function
string intToString(int num, int size);
bool laNamNhuan(int nInput);
