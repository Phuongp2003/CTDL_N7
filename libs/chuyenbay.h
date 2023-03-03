#pragma once
#include "hanhkhach.h"
#include "header.h"
#include "maybay.h"
#include "ngaythang.h"
#define HuyChuyen 0
#define ConVe 1
#define HetVe 2
#define HoanTat 3

#ifndef CHUYENBAY
#define CHUYENBAY

class VeMayBay
{
private:
    string IDVe;
    HanhKhach *HanhKhachMuaVe;

public:
    VeMayBay();
    VeMayBay(string IDVe, HanhKhach *HanhKhachMuaVe);
    void setIDVe(string ID);
    string getIDVe();
    void setHanhKhach(HanhKhach *HanhKhachMuaVe);
    HanhKhach *getHanhKhach();
};

class ChuyenBay
{
private:
    char MaCB[15];
    Date *NgayGio;
    string NoiDen;
    int TrangThai = 1, SoVeToiDa = 0;
    char *idMayBay;
    MayBay *MayBaySuDung;
    VeMayBay *DSVe[MAXVe];

public:
    int SoVeDaDat = 0;
    ChuyenBay();
    /**
     * @brief Nhập thông tin Chuyến Bay CÙNG MỘT LÚC!
     * @note Buộc toàn bộ thông tin phải chính xác!
     * @note Mã chuyến bay lúc nhập yêu cầu ít hơn 15 kí tự!
     */
    ChuyenBay(const char *_MaCB, string _NoiDen,
              Date *_NgayGio, MayBay *_MayBay);
    char *getMaCB();
    string getNoiDen();
    Date *getNgayGio();
    void setNgayGio(Date *_NgayGio);
    /**
     *
     * @param _GiaTri 0-Huỷ chuyến, 1-Còn vé, 2-Hết vé, 3-Hoàn tất
     */
    void setTrangThai(int _TrangThai);
    int getTrangThai();
    MayBay getMayBay();
    void addVeMB(VeMayBay *_Ve);
    void showDSVe();
};

class NODE_ChuyenBay
{
private:
    ChuyenBay *node;
    NODE_ChuyenBay *next;

public:
    NODE_ChuyenBay();
    NODE_ChuyenBay(ChuyenBay *cb);
    bool hasNext();
    NODE_ChuyenBay *getNext();
    void setNext(NODE_ChuyenBay *node_cb_next);
    void themChuyenBay(ChuyenBay *cb);
    void xoaChuyenBaynext();
    ChuyenBay *TimCB(string _MaCB);
    ChuyenBay *getCB();
};

//============================================================================
#include "chuyenbay.h"

// hàm của DSVe

VeMayBay::VeMayBay()
{
    IDVe = "A00";
}

VeMayBay::VeMayBay(string IDVe, HanhKhach *HanhKhachMuaVe)
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

void VeMayBay::setHanhKhach(HanhKhach *HanhKhachMuaVe)
{
    this->HanhKhachMuaVe = HanhKhachMuaVe;
}

HanhKhach *VeMayBay::getHanhKhach()
{
    return this->HanhKhachMuaVe;
}

// hàm của ChuyenBay

ChuyenBay::ChuyenBay()
{
    strcpy(MaCB, "");
    NoiDen = "";
}

ChuyenBay::ChuyenBay(const char *_MaCB, string _NoiDen,
                     Date *_NgayGio, MayBay *_MayBay)
{
    this->MayBaySuDung = _MayBay;
    this->NgayGio = _NgayGio;
    strcpy(this->MaCB, _MaCB);
    this->NoiDen = _NoiDen;
    this->SoVeToiDa =
        this->MayBaySuDung->getSoDay() * MayBaySuDung->getSoDong();
}

char *ChuyenBay::getMaCB()
{
    return this->MaCB;
}

string ChuyenBay::getNoiDen()
{
    return this->NoiDen;
}

Date *ChuyenBay::getNgayGio()
{
    return this->NgayGio;
}

void ChuyenBay::setTrangThai(int _TrangThai)
{
    this->TrangThai = _TrangThai;
}

int ChuyenBay::getTrangThai()
{
    return this->TrangThai;
}

MayBay ChuyenBay::getMayBay()
{
    return *this->MayBaySuDung;
}

void ChuyenBay::addVeMB(VeMayBay *_Ve)
{
    this->DSVe[SoVeDaDat] = _Ve;
    SoVeDaDat++;
}

void ChuyenBay::setNgayGio(Date *_NgayGio)
{
    this->NgayGio = _NgayGio;
}

/**
 * @note hàm chỉ làm mẫu, lúc xuất chỉnh trên UI sau
 */
void ChuyenBay::showDSVe()
{
    for (int i = 0; i < SoVeDaDat; i++)
    {
        HanhKhach *tmp;
        tmp = DSVe[i]->getHanhKhach();
        cout << i << ". " << DSVe[i]->getIDVe()
             << ", CMND: " << tmp->getCmnd()
             << "Ho va Ten: " << tmp->getHo() << " " << tmp->getTen()
             << endl;
    }
}

// Hàm của Node_ChuyenBay

NODE_ChuyenBay::NODE_ChuyenBay()
{
    this->node = NULL;
    this->next = NULL;
}

NODE_ChuyenBay::NODE_ChuyenBay(ChuyenBay *cb)
{
    this->node = cb;
    this->next = NULL;
}

bool NODE_ChuyenBay::hasNext()
{
    if (this->next != NULL)
        return true;
    return false;
}

NODE_ChuyenBay *NODE_ChuyenBay::getNext()
{
    return this->next;
}

void NODE_ChuyenBay::setNext(NODE_ChuyenBay *cb_next)
{
    this->next = cb_next;
}

void NODE_ChuyenBay::themChuyenBay(ChuyenBay *cb)
{
    NODE_ChuyenBay *newNode = new NODE_ChuyenBay();
    newNode->node = cb;
    newNode->next = this->next;
    this->next = newNode;
}

void NODE_ChuyenBay::xoaChuyenBaynext()
{
    if (this->next != NULL && this->next->node->SoVeDaDat == 0)
        this->next = this->next->next;
}

ChuyenBay *NODE_ChuyenBay::TimCB(string _MaCB)
{
    if (this->node->getMaCB() == _MaCB)
        return this->node;
    return NULL;
}
ChuyenBay *NODE_ChuyenBay::getCB(){
    return node;
}
#endif
