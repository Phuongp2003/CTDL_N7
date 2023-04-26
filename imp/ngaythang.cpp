#include "../header/ngaythang.h"
#include <sstream>
#include <string>
using std::string;
Date::Date() {}

Date::Date(int _Ngay, int _Thang, int _Nam, int _Gio, int _Phut) {
  this->Gio = _Gio;
  this->Phut = _Phut;
  this->Ngay = _Ngay;
  this->Thang = _Thang;
  this->Nam = _Nam;
}

void Date::setGio(int _Gio) { this->Gio = _Gio; }

int Date::getGio() { return Gio; }
void Date::setPhut(int Phut) { this->Phut = Phut; }
int Date::getPhut() { return Phut; }
void Date::setNgay(int _Ngay) { this->Ngay = _Ngay; }
int Date::getNgay() { return Ngay; }
void Date::setThang(int Thang) { this->Thang = Thang; }
int Date::getThang() { return Thang; }
void Date::setNam(int Nam) { this->Nam = Nam; }
int Date::getNam() { return Nam; }
void Date::showTG() {
  cout << Gio << ":" << Phut << " " << Ngay << "/" << Thang << "/" << Nam;
}
bool laNamNhuan(int nInput) {
  if ((nInput % 4 == 0 && nInput % 100 != 0) || nInput % 400 == 0) {
    return true;
  }
  return false;
}
bool Date::checkNgay() {
  switch (Thang) {
  // case 0:
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
  case 12:
    if (Ngay >= 0 && Ngay <= 31)
      return true;
    else
      return false;
  case 4:
  case 6:
  case 9:
  case 11:
    if (Ngay >= 0 && Ngay <= 30)
      return true;
    else
      return false;
  case 2:
    switch (laNamNhuan(Nam)) {
    case true:
      if (Ngay >= 0 && Ngay <= 29)
        return true;
      else
        return false;

    case false:
      if (Ngay >= 0 && Ngay <= 28)
        return true;
      else
        return false;
    }
  }
  return false;
}
bool Date::checkGio() {
  if (Gio >= 0 && Gio <= 23 && Phut >= 0 && Phut <= 59)
    return true;
  else
    return false;
}
bool Date::checkNgayNhapVoiNgayHT() {
  time_t now = time(0);
  tm *ltm = localtime(&now);
  bool t_nam = 0;
  bool t_thang = 0;
  bool t_ngay = 0;

  if (Nam < 1900 + ltm->tm_year)
    t_nam = false;
  else
    t_nam = true;
  if (Thang >= 1 + ltm->tm_mon)
    t_thang = true;
  else
    t_thang = false;
  if (Ngay >= (ltm->tm_mday) + 1)
    t_ngay = true;
  else
    t_ngay = false;
  if (t_nam && t_thang && t_ngay)
    return true; // là thời gian nhập vào hợp lý
  return false;
}

bool Date::checkGioNhapVoiGioHT() {
  time_t now = time(0);
  tm *ltm = localtime(&now);
  bool t_gio = 0;
  bool t_phut = 0;
  if (Gio >= ltm->tm_hour)
    t_gio = true;
  else
    t_gio = false;
  if (Phut >= (ltm->tm_min) + 1)
    t_phut = true;
  else
    t_phut = false;
  if (t_gio && t_phut)
    return true; // là thời gian nhập vào hợp lý
  return false;
}

bool Date::checkDateHour() // để set trang thái hoàn thành của chuyến bay
{
  time_t now = time(0);
  tm *ltm = localtime(&now);
  bool t_nam = 0;
  bool t_thang = 0;
  bool t_ngay = 0;
  bool t_gio = 0;
  bool t_phut = 0;
  if (Nam == 1900 + ltm->tm_year)
    t_nam = false;
  else
    t_nam = true;
  if (Thang == 1 + ltm->tm_mon)
    t_thang = true;
  else
    t_thang = false;
  if (Ngay == (ltm->tm_mday))
    t_ngay = true;
  else
    t_ngay = false;
  if (Gio == ltm->tm_hour)
    t_gio = true;
  else
    t_gio = false;
  if (Phut == (ltm->tm_min))
    t_phut = true;
  else
    t_phut = false;
  if (t_nam && t_thang && t_ngay && t_gio && t_phut)
    return true; // là thời gian nhập vào hợp lý
  return false;
}

string Date::PrintDateHour() //
{
  return intToString(Ngay, 2) + "/" + intToString(Thang, 2) + "/" +
         intToString(Nam, 4) + " " + intToString(Gio, 2) + ":" +
         intToString(Phut, 2);
}

// void Date::PrintDateHour_c(char *result) //
// {
//     result[0] = 0;
//     char *dd = intTochar(Ngay, 2),
//          *mm = intTochar(Thang, 2),
//          *yyyy = intTochar(Nam, 4),
//          *hh = intTochar(Gio, 2),
//          *pp = intTochar(Phut, 2);

//     strcat(result, dd);
//     strcat(result, " / ");
//     strcat(result, mm);
//     strcat(result, " / ");
//     strcat(result, yyyy);
//     strcat(result, "  ");
//     strcat(result, hh);
//     strcat(result, " : ");
//     strcat(result, pp);
//     result[23] = 0;
// }

string Date::PrintDate() {
  return intToString(Ngay, 2) + '/' + intToString(Thang, 2) + '/' +
         intToString(Nam, 4);
}
string Date::PrintHour() {
  return intToString(Gio, 2) + ":" + intToString(Phut, 2);
}

void Date::setToNow() {
  time_t now = time(0);
  tm *ltm = localtime(&now);
  Ngay = ltm->tm_mday;
  Thang = ltm->tm_mon + 1;
  Nam = ltm->tm_year + 1900;
  Gio = ltm->tm_hour;
  Phut = ltm->tm_min;
}

bool Date::operator<(Date another) {
  if (Nam < another.Nam)
    return true;
  else if (Nam > another.Nam)
    return false;

  if (Thang < another.Thang)
    return true;
  else if (Thang > another.Thang)
    return false;

  if (Ngay < another.Ngay)
    return true;
  else if (Ngay > another.Ngay)
    return false;

  if (Gio < another.Gio)
    return true;
  else if (Gio > another.Gio)
    return false;

  if (Phut < another.Phut)
    return true;
  else if (Phut > another.Phut)
    return false;

  return false;
}

bool Date::operator==(Date another) {
  if (Nam != another.Nam)
    return false;

  if (Thang != another.Thang)
    return false;

  if (Ngay != another.Ngay)
    return false;

  return true;
}

string intToString(int num, int size) {
  std::stringstream ss;
  ss << num;

  std::string str = ss.str();
  if (str.length() < size) {
    int len = str.length();
    for (int i = 0; i < size - len; i++) {
      str = "0" + str;
    }
  }

  str[size] = 0;

  return str;
}