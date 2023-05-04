#pragma once
#include "header.h"
class Date {
private:
  int phut;
  int gio;
  int ngay;
  int thang;
  int nam;

public:
  Date();
  Date(int ngay, int thang, int nam, int gio, int phut);
  void setToNow();
  void setGio(int);
  int getGio();
  void setPhut(int);
  int getPhut();
  void setNgay(int);
  int getNgay();
  void setThang(int);
  int getThang();
  void setNam(int);//
  int getNam();
  void showTG();
  bool checkNgay();
  bool checkGio();
  bool checkNgayNhapVoiNgayHT();
  bool checkGioNhapVoiGioHT();
  bool checkDateHour();
  string printDateHour();
  const char *printDateHour_c();
  string printDate();
  string printHour();
  Date ngayHoanThanh();
  long long soVoi1_1_1900_0_0();
  
  

  bool operator<(Date another);
  bool operator==(Date another);
};
// dd/mm/yyyy hh:mm
// function
string intToString(int num, int size);
bool laNamNhuan(int nInput); //
