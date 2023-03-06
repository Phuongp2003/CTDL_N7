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
    void setGio(int, int);
    int getGio();
    void setNgay(int, int, int);
    int getNgay();
    void showTG();
    bool checkNgay(int ,int,int);
    bool checkGio(int,int);
};

#endif