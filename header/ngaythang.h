#pragma once
#include "header.h"
class Date
{
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
  void setNam(int);
  int getNam();
  bool checkNgay();
  bool checkNgayNhapVoiNgayHT();
  string printDateHour();
  string printDate();
  string printHour();
  long long soVoi1_1_1900_0_0();

  bool operator<(const Date &another);
  bool operator==(const Date &another);
};
