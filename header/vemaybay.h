#pragma once

// #include "chuyenbay.h"
// #include "hanhkhach.h"
#include "maybay.h"
// #include "ngaythang.h"

#include "header.h"

class VeMayBay {
private:
  string IDVe;
  string CMND;
  bool TrangThai; // false là đã đặt

public:
  VeMayBay();
  VeMayBay(string CMND);
  void setIDVe(string ID);
  string getIDVe();
  void setHanhKhach(string CMND);
  string getHanhKhach();
  // void setTrangThai(bool TrangThai);
  // bool getTrangThai();
};

class DSVeMayBay {
private:
  VeMayBay *DSVeMB;
  int SoVeToiDa;
  int SoVeDaDat;

public:
  DSVeMayBay();

  void setSoVeToiDa(int SoVeToiDa);
  void setSoVeDaDat(int SoVeDaDat);

  int getSoVeToiDa();
  int getSoVeDaDat();
  int getSoVeConLai();
  VeMayBay *getDSVeMB();
  void setDSVe(MayBay *MB);
  void setVe(VeMayBay Ve, int pos);
  VeMayBay getVe(int index);
  ~DSVeMayBay();
};
