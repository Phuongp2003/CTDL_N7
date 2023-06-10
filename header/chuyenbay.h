#pragma once

#include "hanhkhach.h"
#include "header.h"
#include "maybay.h"
#include "ngaythang.h"
#include "vemaybay.h"

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
  ChuyenBay();
  ChuyenBay(const char *maCB, string noiDen, Date ngayGio,
            const char *maMayBay);

  DsVeMayBay getDSVe();
  char *getMaCB();
  Date getNgayGio();
  string getNoiDen();
  int getTrangThai();

  void setDSVe(DsVeMayBay dsVe);
  void setidMayBay(const char *idMayBay);
  const char *getMaMayBay();
  void setNgayGio(Date ngayGio);
  /**
   *
   * @param _GiaTri 0-Huỷ chuyến, 1-Còn vé, 2-Hết vé, 3-Hoàn tất
   */
  void setTrangThai(int trangThai);

  bool checkNoiDen(const char *noiDen);
  bool checkMaCB(const char *maCB);
  bool checkTime(Date time);

  void ThucHienCB(DsMayBay DsMB);
  Date ngayHoanThanh();
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
  NodeCB *getNext();
  NodeCB *getTail();

  void setCb(ChuyenBay chuyenBay);
  void setNext(NodeCB *next);

  bool hasNext();

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
  void setSize();

  NodeCB *getHead();
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
  int duocDatKhong(string cmnd, ChuyenBay cb);

  void readFromFile(DsMayBay &listMB);
  void writetToFile();

  bool update(DsMayBay DsMB);
  bool isAval(const char *soHieuMB, Date timeCb, const char *_maCB);
  bool isExist(const char *maCB);
  bool isUsing(const char *maMB);
};

void getDataFromFile(DsChuyenBay &listCB, DsMayBay &listMB, DsHanhKhach &listHK); //
void setDataToFile(DsChuyenBay &listCB, DsMayBay &listMB, DsHanhKhach &listHK);
