#pragma once
#include "hanhkhach.h"
#include "header.h"
#include "maybay.h"
#include "ngaythang.h"
#include  "vemaybay.h"

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



class ChuyenBay
{
private:
    char MaCB[15];
    Date NgayGio;
    string NoiDen;
    int TrangThai;
    // char *idMayBay;
    char IDMayBay[16];
    DSVeMayBay *DSVe;

public:
    /**
     * @brief Nhập thông tin Chuyến Bay CÙNG MỘT LÚC!
     * @note Buộc toàn bộ thông tin phải chính xác!
     * @note Mã chuyến bay lúc nhập yêu cầu ít hơn 15 kí tự!
     */
    ChuyenBay();
    ChuyenBay(const char *_MaCB, string _NoiDen,
              Date _NgayGio, char *_MaMayBay);
    char *getMaCB();
    string getNoiDen();
    Date getNgayGio();
    void setNgayGio(Date _NgayGio);
    /**
     *
     * @param _GiaTri 0-Huỷ chuyến, 1-Còn vé, 2-Hết vé, 3-Hoàn tất
     */
    void setTrangThai(int _TrangThai);
    int getTrangThai();
    int getSoVeToiDa();
    char *getMaMayBay();
    void setDSVeMB(DSMB *DanhSachCB);

    void showDSVe();
    VeMayBay *getDSVe();
    void ThucHienCB(DSMB *DanhSachCB);
    // node
};
class Node_CB
{
private:
    ChuyenBay *node;
    Node_CB *next;

public:
    ChuyenBay *getNode();
    bool hasNext();
    void setNext(Node_CB *node);
    Node_CB *getNext();
};

class DanhSachCB
{
private:
    Node_CB *head;
    int size;

public:
    DanhSachCB();
    DanhSachCB(Node_CB *cb);
    void push(Node_CB *currNode, Node_CB *node);
    void push_back(Node_CB *node);
    void push_front(Node_CB *node);
    /**
     * @brief xoá chuyến bay hiện chọn
     *
     */
    void pop(Node_CB *node);
    void pop_first();
    void pop_back();
    ChuyenBay *TimCB(string _MaCB);
};

#endif
