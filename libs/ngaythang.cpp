#include "ngaythang.h"
using namespace std;

Date::Date() {}

Date::Date(int _Gio, int _Phut, int _Ngay, int _Thang, int _Nam)
{
    this->Gio = _Gio;
    this->Phut = _Phut;
    this->Ngay = _Ngay;
    this->Thang = _Thang;
    this->Nam = _Nam;
}

void Date::setGio(int _Gio, int _Phut)
{
    this->Gio = _Gio;
    this->Phut = _Phut;
}
void Date::setNgay(int _Ngay, int _Thang, int _Nam)
{
    this->Ngay = _Ngay;
    this->Thang = _Thang;
    this->Nam = _Nam;
}

void Date::showTG()
{
    cout << Gio << ":" << Phut << " "
         << Ngay << "/" << Thang << "/" << Nam;
}
