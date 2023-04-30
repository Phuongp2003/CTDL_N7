#pragma once

#include "header.h"

#include "hanhkhach.h"
#include "maybay.h"
#include "ngaythang.h"
#include "vemaybay.h"

#define HuyChuyen 0
#define ConVe 1
#define HetVe 2
#define HoanTat 3
class ChuyenBay {
private:
  char MaCB[15];
  Date NgayGio;
  string NoiDen;
  int TrangThai;
  char IDMayBay[16];
  DSVeMayBay DSVe;

public:
  /**
   * @brief Nhập thông tin Chuyến Bay CÙNG MỘT LÚC!
   * @note Buộc toàn bộ thông tin phải chính xác!
   * @note Mã chuyến bay lúc nhập yêu cầu ít hơn 15 kí tự!
   */
  ChuyenBay();
  ChuyenBay(const char *_MaCB, string _NoiDen, Date _NgayGio,
            const char *_MaMayBay);
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
  const char *getMaMayBay();

  bool checkNoiDen(const char *noiden);
  bool checkTime(int ngay, int thang, int nam, int gio, int phut);
  bool checkMaCB(const char *maCB);

  void setDSVe(DSVeMayBay dsve);
  DSVeMayBay getDSVe();

  void ThucHienCB(DSMB *DanhSachCB);
  Date NgayHoanThanh();
  
  // node
  bool operator<(const ChuyenBay &other);
};

class NodeCB {
private:
  ChuyenBay node;
  NodeCB *next;

public:
  NodeCB();
  NodeCB(ChuyenBay node);
  ChuyenBay getNode();
  void setNode(ChuyenBay node);
  bool hasNext();
  void setNext(NodeCB *node);
  NodeCB *getNext();
  NodeCB *getTail();
  bool Cach6tiengchua(Date another);
  ~NodeCB();
};

class DanhSachCB {
private:
  NodeCB *head;
  int size;

public:
  DanhSachCB();
  DanhSachCB(NodeCB *cb);
  void setHead(NodeCB *head);
  NodeCB *getHead();

  void setSize();
  int getSize();
  void push(NodeCB *currNode, NodeCB *node);
  void push_back(NodeCB *node);
  void push_front(NodeCB *node);
  void insertOrder(NodeCB *node);

  /**
   * @brief xoá chuyến bay hiện chọn
   *
   */
  void pop(NodeCB *node);
  void pop_first(); //
  void pop_back();
  ChuyenBay TimCB(string _MaCB);
  bool MayBayDangSuDung(const char *SoHieuMB);
  bool DuocDatKhong(string CMND, ChuyenBay cb);

  void ReadFromFile(ifstream &file);
  void WritetToFile(ofstream &file);
  NodeCB *merge(NodeCB *left, NodeCB *right);
  NodeCB *mid_point(NodeCB *node);
  NodeCB *sort(NodeCB *node);

  bool update();
};

void linkAllLists(DSMB listMB, DsHanhKhach listHK, DanhSachCB listCB);