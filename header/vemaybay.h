#pragma once
#include "hanhkhach.h"
#include "header.h"
#include "maybay.h"
#include "ngaythang.h"

class VeMayBay
{
private:
    string IDVe;
    string CMND;
    bool TrangThai; // false là đã đặt

public:
    VeMayBay();
    VeMayBay(string IDVe, string CMND);
    void setIDVe(string ID);
    string getIDVe();
    void setHanhKhach(string CMND);
    string getHanhKhach();
    void setTrangThai(bool TrangThai);
    bool getTrangThai();
};

class DSVeMayBay
{
private:
    VeMayBay *DSVeMB;
    int SoVeToiDa;
    int SoVeDaDat;

public:
    DSVeMayBay();
    void setSoVeToiDa(int SoVeToiDa);
    int getSoVeToiDa();
    VeMayBay *getDSVeMB();
    void setDSVe(MayBay *MB);
    ~DSVeMayBay();
};
