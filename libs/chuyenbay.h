#include "hanh_khach.h"
#include "header.h"
#include "maybay.h"
#include "ngaythang.h"

class VeMayBay
{
private:
    string IDVe = "A00";
    Hanh_Khach HanhKhachMuaVe;

public:
    VeMayBay();
    VeMayBay(string IDVe, Hanh_Khach HanhKhachMuaVe);
    void setIDVe(string ID);
    string getIDVe();
    void setHanhKhach(Hanh_Khach HanhKhachMuaVe);
    Hanh_Khach getHanhKhach();
};

class ChuyenBay
{
private:
    string MaCB = "", NoiDen = "";
    Date NgayGio;
    int TrangThai = 1, SoVeToiDa = 0;
    MayBay *MayBaySuDung = new MayBay();
    VeMayBay DSVe[MAXVe];

public:
    int SoVeDatDat = 0;
    ChuyenBay();
    ChuyenBay(string _MaCB, string _NoiDen,
              Date _NgayGio, MayBay _MayBay);
    string getMaCB();
    string getNoiDen();
    Date getNgayGio();
    int getTrangThai();
    MayBay getMayBay();
    void showDSVe();
};

class NODE_ChuyenBay
{
private:
    ChuyenBay node;
    NODE_ChuyenBay *next;

public:
    NODE_ChuyenBay();
    NODE_ChuyenBay(ChuyenBay *cb);
    bool hasNext();
    NODE_ChuyenBay *getNext();
    void setNext(NODE_ChuyenBay *cb_next);
};

//============================================================================

// hàm của DSVe

VeMayBay::VeMayBay() {}

VeMayBay::VeMayBay(string IDVe, Hanh_Khach HanhKhachMuaVe)
{
    this->IDVe = IDVe;
    this->HanhKhachMuaVe = HanhKhachMuaVe;
}

void VeMayBay::setIDVe(string ID)
{
    this->IDVe = ID;
}

string VeMayBay::getIDVe()
{
    return this->IDVe;
}

void VeMayBay::setHanhKhach(Hanh_Khach HanhKhachMuaVe)
{
    this->HanhKhachMuaVe = HanhKhachMuaVe;
}

Hanh_Khach VeMayBay::getHanhKhach()
{
    return this->HanhKhachMuaVe;
}

// hàm của ChuyenBay

ChuyenBay::ChuyenBay() {}

ChuyenBay::ChuyenBay(string _MaCB, string _NoiDen,
                     Date _NgayGio, MayBay _MayBay)
{
    this->MayBaySuDung = &_MayBay;
    this->NgayGio = _NgayGio;
    this->MaCB = _MaCB;
    this->NoiDen = _NoiDen;
    this->SoVeToiDa =
        this->MayBaySuDung->soDay * this->MayBaySuDung->soDong;
}

string ChuyenBay::getMaCB()
{
    return this->MaCB;
}

string ChuyenBay::getNoiDen()
{
    return this->NoiDen;
}

Date ChuyenBay::getNgayGio()
{
    return this->NgayGio;
}

int ChuyenBay::getTrangThai()
{
    return this->TrangThai;
}

MayBay ChuyenBay::getMayBay()
{
    return *this->MayBaySuDung;
}

/**
 * @note chưa lấy thông tin khách hàng
 */
void ChuyenBay::showDSVe()
{
}

/**
 * @todo chưa xử lý danh sách chuyến bay
 *
 */