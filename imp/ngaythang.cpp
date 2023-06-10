#include "../header/ngaythang.h"
#include <sstream>
#include <string>

Date::Date()
{
  this->ngay = 0;
  this->thang = 0;
  this->nam = 0;
  this->gio = 0;
  this->phut = 0;
}

Date::Date(int ngay, int thang, int nam, int gio, int phut)
{
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

bool Date::checkNgay()
{
  switch (thang)
  {
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
    switch (laNamNhuan(nam))
    {
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

bool Date::checkNgayNhapVoiNgayHT()
{ // hàm check xem ngày khởi hành của chuyến bay khi nhập vào có hợp lí không
  time_t now = time(0);

  Date _now;
  _now.setToNow();
  if ((Date(ngay, thang, nam, gio, phut).soVoi1_1_1900_0_0() - _now.soVoi1_1_1900_0_0()) >= 12 * 60)
    return true;
  return false;
}

string Date::printDateHour() //
{
  return this->printDate() + " " + this->printHour();
}

string Date::printDate()
{
  return intToString(ngay, 2) + '/' + intToString(thang, 2) + '/' +
         intToString(nam, 4);
}
string Date::printHour()
{
  return intToString(gio, 2) + ":" + intToString(phut, 2);
}

long long Date::soVoi1_1_1900_0_0()
{
  long long dateOfYear = 0, dateOfMonth = 0, date = 0;
  for (int i = 1900; i < nam; i++)
  {
    if (laNamNhuan(nam))
      dateOfYear += 366;
    else
      dateOfYear += 365;
  }
  int a[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (laNamNhuan(nam))
    a[1] = 29;
  if (thang > 1)
  {
    for (int i = 1; i < thang; i++)
    {
      dateOfMonth += a[i - 1];
    }
  } //
  date = ngay - 1;
  return (dateOfYear + dateOfMonth + date) * 24 * 60 + gio * 60 + phut;
}

void Date::setToNow()
{
  time_t now = time(0);
  tm *ltm = localtime(&now);
  ngay = ltm->tm_mday;
  thang = ltm->tm_mon + 1;
  nam = ltm->tm_year + 1900;
  gio = ltm->tm_hour;
  phut = ltm->tm_min;
}

bool Date::operator<(const Date &another)
{
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

bool Date::operator==(const Date &another)
{
  if (nam != another.nam)
    return false;

  if (thang != another.thang)
    return false;

  if (ngay != another.ngay)
    return false;

  return true;
}
