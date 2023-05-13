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
class ChuyenBay
{
private:
  char maCB[15];
  Date ngayGio;
  string noiDen;
  int trangThai;
  char idMayBay[16];
  DsVeMayBay dsVe;

public:
  /**
   * @brief Nhập thông tin Chuyến Bay CÙNG MỘT LÚC!
   * @note Buộc toàn bộ thông tin phải chính xác!
   * @note Mã chuyến bay lúc nhập yêu cầu ít hơn 15 kí tự!
   */
  ChuyenBay();
  ChuyenBay(const char *maCB, string noiDen, Date ngayGio,
            const char *maMayBay);
  
  char *getMaCB();
  string getNoiDen();
  Date getNgayGio();
  void setNgayGio(Date ngayGio);

  /**
   *
   * @param _GiaTri 0-Huỷ chuyến, 1-Còn vé, 2-Hết vé, 3-Hoàn tất
   */
  void setTrangThai(int trangThai);
  int getTrangThai();
  void setidMayBay(const char* idMayBay);
  const char *getMaMayBay();

  bool checkNoiDen(const char *noiDen);
  bool checkTime(Date time);
  bool checkMaCB(const char *maCB);

  void setDSVe(DsVeMayBay dsVe);
  DsVeMayBay getDSVe();

  void ThucHienCB(DsMayBay DsMB);
  Date ngayHoanThanh();
  // int soSanhNgay(Date another);
  bool cach(int hour, Date another);

  // node
  bool operator<(const ChuyenBay &other);
};

class NodeCB
{
private:
  ChuyenBay chuyenBay;
  NodeCB *next;

public:
  NodeCB();
  NodeCB(ChuyenBay chuyenBay);
  ChuyenBay getNode();
  void setCb(ChuyenBay chuyenBay);
  bool hasNext();
  void setNext(NodeCB *next);
  NodeCB *getNext();
  NodeCB *getTail();
  bool Cach6tiengchua(Date another);
  ~NodeCB();
};

class DsChuyenBay
{
private:
  NodeCB *head;
  int size;

public:
  DsChuyenBay();
  DsChuyenBay(NodeCB *cb);
  void setHead(NodeCB *head);
  NodeCB *getHead();

  void setSize();
  int getSize();
  void push(NodeCB *currNode, NodeCB *node);
  void pushBack(NodeCB *node);
  void pushFront(NodeCB *node);
  void insertOrder(NodeCB *node);
  //
  /**
   * @brief xoá chuyến bay hiện chọn
   *
   */
  void pop(NodeCB *node);
  void popFirst(); //
  void popBack();
  NodeCB *timCB(string maCB);
  bool duocDatKhong(string cmnd, ChuyenBay cb);

  void readFromFile(DsMayBay listMB);
  void writetToFile();

  bool update(DsMayBay DsMB);
  bool isAval(const char *soHieuMB, Date timeCb, const char *_maCB);
  bool isExist(const char *maCB);
  bool isUsing(const char *maMB);
};
void getDataFromFile(DsChuyenBay &listCB, DsMayBay &listMB, DsHanhKhach &listHK); //
void setDataToFile(DsChuyenBay &listCB, DsMayBay &listMB, DsHanhKhach &listHK);
