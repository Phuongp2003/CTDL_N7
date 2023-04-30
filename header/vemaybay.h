#pragma once

// #include "chuyenbay.h"
// #include "hanhkhach.h"
#include "maybay.h"
// #include "ngaythang.h"

#include "header.h"

class VeMayBay
{
private:
  string idVe;
  string cmnd;
  // bool trangThai; // false là đã đặt

public: //
  VeMayBay();
  VeMayBay(string cmnd);
  void setIDVe(string id);
  string getIDVe();
  void setHanhKhach(string cmnd);
  string getHanhKhach();
  // void setTrangThai(bool trangThai);
  // bool getTrangThai();
};

class DsVeMayBay
{
private:
  VeMayBay *dsVeMB;
  int soVeToiDa;
  int soVeDaDat;

public:
  DsVeMayBay();

  void setSoVeToiDa(int soVeToiDa);
  void setSoVeDaDat(int soVeDaDat);

  int getSoVeToiDa();
  int getSoVeDaDat();
  int getSoVeConLai();
  VeMayBay *getDSVeMB();
  void setDSVe(MayBay *mayBay);
  void setVe(VeMayBay ve, int pos);
  VeMayBay getVe(int index);
  ~DsVeMayBay();
};
