#pragma once
// #include "chuyenbay.h"
#include "header.h"
#include <fstream>
#define MAXMB 300

using std::ifstream;
using std::ios;
using std::ofstream;
// DsMayBay *DanhSach;

class MayBay
{
private:
  char soHieuMB[16]; // @note xây dựng hàm chỉ cho phép nhập 16 kí tự
  char loaiMB[41];   // 41 kí tự
  int soDay;
  int soDong;
  int soLuotThucHienCB;

public: //
  MayBay();
  MayBay(const char *soHieuMB, const char *loaiMB, int soDay, int soDong);
  MayBay(const char *soHieuMB, const char *loaiMB, int soDay, int soDong, int soLuotThucHienCB);
  void setSoHieuMB(const char *soHieuMB);
  char *getSoHieuMB();
  void setLoaiMB(const char *loaiMB);
  char *getLoaiMB();
  void setSoDay(int soDay);
  int getSoDay();
  void setSoDong(int soDong);
  int getSoDong();
  int getSoCho();
  void showMB();
  bool kiemTraSoCho();
  void tangSoLuotThucHienCB();
  int getSoLuotBay();

  MayBay *getMB();
  ~MayBay();
};

// Danh sách con trỏ của máy bay
//======================================================================
class DsMayBay
{
private:
  int size = 0;
  MayBay *data[MAXMB];

public:
  DsMayBay();
  int getSize();
  bool isEmpty();
  bool isFull();
  void insertMB(MayBay *mayBay);
  void deleteMB(int index);
  int findPosMB(const char *soHieuMB);
  MayBay *findMB(const char *soHieuMB);
  DsMayBay findDsMB(const char *soHieuMB);
  void deleteDsMB();
  MayBay *getMB(int index);
  int *sapXepThongKe();
  void readFromFile();
  void writetoFile();
  void writetoFileWhenAdd();
  bool planeMatch(const char* soHieuMB,const char* other);
  ~DsMayBay(); //
};
