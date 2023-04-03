#pragma once
#include "hanhkhach.h"
#include "header.h"
#include "maybay.h"
#include "ngaythang.h"
#include "vemaybay.h"

using std::string;

#define HuyChuyen 0
#define ConVe 1
#define HetVe 2
#define HoanTat 3

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
    char *getMaMayBay();
    // void setDSVeMB(DSMB *DanhSachCB);

    // void showDSVe();
    DSVeMayBay *getDSVe();

    void ThucHienCB(DSMB *DanhSachCB);
    // node
};

class NodeCB
{
private:
    ChuyenBay *node;
    NodeCB *next;

public:
    ChuyenBay *getNode();
    bool hasNext();
    void setNext(NodeCB *node);
    NodeCB *getNext();
};

class DanhSachCB
{
private:
    NodeCB *head;
    int size;

public:
    DanhSachCB();
    DanhSachCB(NodeCB *cb);
    NodeCB *getHead();
    void push(NodeCB *currNode, NodeCB *node);
    void push_back(NodeCB *node);
    void push_front(NodeCB *node);
    /**
     * @brief xoá chuyến bay hiện chọn
     *
     */
    void pop(NodeCB *node);
    void pop_first();
    void pop_back();
    ChuyenBay *TimCB(string _MaCB);
    DanhSachCB TimDSCB(Date date, string noiden);

    DanhSachCB LocDSCB(string _keyword);
};