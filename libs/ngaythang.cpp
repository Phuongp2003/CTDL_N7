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

void Date::setGio(int _Gio)
{
    this->Gio = _Gio;
}

int Date::getGio(){
    return Gio;
}
void Date::setPhut(int Phut)
{
    this->Phut = Phut;
}
int Date::getPhut(){
    return Phut;
}
void Date::setNgay(int _Ngay)
{
    this->Ngay = _Ngay;

}
int Date::getNgay(){
    return Ngay;
}
void Date::setThang(int Thang)
{
    this->Thang = Thang;

}
int Date::getThang(){
    return Thang;
}
void Date::setNam(int Nam)
{
    this->Nam = Nam;

}
int Date::getNam(){
    return Nam;
}
void Date::showTG()
{
    cout << Gio << ":" << Phut << " "
         << Ngay << "/" << Thang << "/" << Nam;
}
bool laNamNhuan(int nInput)
{
	if ((nInput % 4 == 0 && nInput % 100 != 0) || nInput % 400 == 0)
	{
		return true;
	}
	return false;
}
bool Date::checkNgay(int Ngay,int Thang,int Nam){
    switch(Thang)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if(Ngay>=0 && Ngay<=31) return true;
            else return false;
        case 4:
        case 6:
        case 9:
        case 11:
            if(Ngay>=0 && Ngay<=30) return true;
            else return false;
        case 2:
            switch(laNamNhuan(Nam))
            {
                case true:
                    if(Ngay>=0 && Ngay<=29) return true;
                    else return false;
    
                case false:
                    if(Ngay>=0 && Ngay<=28) return true;
                    else return false;
            }
            
    }

}
bool Date::checkGio(int Gio,int Phut){
    if(Gio >=0 && Gio<=23 && Phut>=0 && Phut<=59) return true;
    else return false;
}