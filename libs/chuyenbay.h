#pragma once
#include "hanhkhach.h"
#include "header.h"
#include "maybay.h"
#include "ngaythang.h"

using std::string;

#define HuyChuyen 0
#define ConVe 1
#define HetVe 2
#define HoanTat 3

#ifndef CHUYENBAY
#define CHUYENBAY

const char IDChu[26] = {
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
    'G',
    'H',
    'I',
    'J',
    'K',
    'L',
    'M',
    'N',
    'O',
    'P',
    'Q',
    'R',
    'S',
    'T',
    'U',
    'V',
    'W',
    'X',
    'Y',
    'Z',
};

const char IDSo[10] = {'0', '1', '2', '3', '4',
                       '5', '6', '7', '8', '9'};

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
    int TrangThai, SoVeToiDa;
    // char *idMayBay;
    MayBay *MayBaySuDung = NULL;
    VeMayBay **DSVe;
    int SoVeDaDat = 0;
    ChuyenBay *next;

public:
    /**
     * @brief Nhập thông tin Chuyến Bay CÙNG MỘT LÚC!
     * @note Buộc toàn bộ thông tin phải chính xác!
     * @note Mã chuyến bay lúc nhập yêu cầu ít hơn 15 kí tự!
     */
    ChuyenBay();
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
    MayBay *getMayBay();
    void setDSVeMB();
    void showDSVe();
    // node
};

class DanhSachCB
{
private:
    struct Node
    {
        ChuyenBay *node;
        Node *next;
    };
    Node *head;
    int size;

public:
    DanhSachCB();
    DanhSachCB(Node *cb);
    bool hasNext(Node *currNode);
    void setNext(Node *currNode, Node *node);
    Node *getNext(Node *currNode);
    void push(Node *currNode, Node *node);
    void push_back(Node *node);
    void push_front(Node *node);
    /**
     * @brief xoá chuyến bay hiện chọn
     *
     */
    void pop(Node *node);
    void pop_first();
    void pop_back();
    ChuyenBay *TimCB(string _MaCB);
};

#endif