#include "../header/ngaythang.h"
#include <sstream>
#include <string>
using std::string;
Date::Date() {}

Date::Date(int ngay, int thang, int nam, int gio, int phut) {
  this->gio = gio;
  this->phut = phut;
  this->ngay = ngay;
  this->thang = thang;
  this->nam = nam;
}

void Date::setGio(int gio) { this->gio = gio; }

int Date::getGio() { return this->gio; }

void Date::setPhut(int phut) { this->phut = phut; }

int Date::getPhut() { return this->phut; }

void Date::setNgay(int ngay) { this->ngay = ngay; }

int Date::getNgay() { return this->ngay; }

void Date::setThang(int thang) { this->thang = thang; }

int Date::getThang() { return this->thang; }

void Date::setNam(int nam) { this->nam = nam; }

int Date::getNam() { return this->nam; }

void Date::showTG() {
  cout << gio << ":" << phut << " " << ngay << "/" << thang << "/" << nam;
}

bool laNamNhuan(int nInput) {
  if ((nInput % 4 == 0 && nInput % 100 != 0) || nInput % 400 == 0) {
    return true;
  }
  return false;
}

bool Date::checkNgay() {
  switch (thang) {
  // case 0:
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
  case 12:
    if (ngay >= 0 && ngay <= 31)
      return true;
    else
      return false;
  case 4:
  case 6:
  case 9:
  case 11:
    if (ngay >= 0 && ngay <= 30)
      return true;
    else
      return false;
  case 2:
    switch (laNamNhuan(nam)) {
    case true:
      if (ngay >= 0 && ngay <= 29)
        return true;
      else
        return false;

    case false:
      if (ngay >= 0 && ngay <= 28)
        return true;
      else
        return false;
    }
  }
  return false;
}

bool Date::checkGio() {
  if (gio >= 0 && gio <= 23 && phut >= 0 && phut <= 59)
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

  if (nam < 1900 + ltm->tm_year)
    t_nam = false;
  else
    t_nam = true;
  if (thang >= 1 + ltm->tm_mon)
    t_thang = true;
  else
    t_thang = false;
  if (ngay >= (ltm->tm_mday) + 1)
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
  if (gio >= ltm->tm_hour)
    t_gio = true;
  else
    t_gio = false;
  if (phut >= (ltm->tm_min) + 1)
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
  if (nam == 1900 + ltm->tm_year)
    t_nam = false;
  else
    t_nam = true;
  if (thang == 1 + ltm->tm_mon)
    t_thang = true;
  else
    t_thang = false;
  if (ngay == (ltm->tm_mday))
    t_ngay = true;
  else
    t_ngay = false;
  if (gio == ltm->tm_hour)
    t_gio = true;
  else
    t_gio = false;
  if (phut == (ltm->tm_min))
    t_phut = true;
  else
    t_phut = false;
  if (t_nam && t_thang && t_ngay && t_gio && t_phut)
    return true; // là thời gian nhập vào hợp lý
  return false;
}

string Date::printDateHour() //
{
  return intToString(ngay, 2) + "/" + intToString(thang, 2) + "/" +
         intToString(nam, 4) + " " + intToString(gio, 2) + ":" +
         intToString(phut, 2);
}

// void Date::PrintDateHour_c(char *result) //
// {
//     result[0] = 0;
//     char *dd = intTochar(Ngay, 2),
//          *mm = intTochar(thang, 2),
//          *yyyy = intTochar(Nam, 4),
//          *hh = intTochar(Gio, 2),
//          *pp = intTochar(phut, 2);

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

string Date::printDate() {
  return intToString(ngay, 2) + '/' + intToString(thang, 2) + '/' +
         intToString(nam, 4);
}
string Date::printHour() {
  return intToString(gio, 2) + ":" + intToString(phut, 2);
}

void Date::setToNow() {
  time_t now = time(0);
  tm *ltm = localtime(&now);
  ngay = ltm->tm_mday;
  thang = ltm->tm_mon + 1;
  nam = ltm->tm_year + 1900;
  gio = ltm->tm_hour;
  phut = ltm->tm_min;
}

bool Date::operator<(Date another) {
  if (nam < another.nam)
    return true;
  else if (nam > another.nam)
    return false;

  if (thang < another.thang)
    return true;
  else if (thang > another.thang)
    return false;

  if (ngay < another.ngay)
    return true;
  else if (ngay > another.ngay)
    return false;

  if (gio < another.gio)
    return true;
  else if (gio > another.gio)
    return false;

  if (phut < another.phut)
    return true;
  else if (phut > another.phut)
    return false;

  return false;
}

bool Date::operator==(Date another) {
  if (nam != another.nam)
    return false;

  if (thang != another.thang)
    return false;

  if (ngay != another.ngay)
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
