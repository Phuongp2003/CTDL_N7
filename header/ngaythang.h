#pragma once
#include "header.h"

#ifndef NGAYTHANG
#define NGAYTHANG

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
    bool checkNgay(int ,int,int);
    bool checkGio(int,int);

};

#endif