#include "../header/maybay.h"

using namespace std;

MayBay::MayBay() {}
MayBay::MayBay(const char *_SoHieuMB, const char *LoaiMB, int SoDay, int SoDong)
{
    strncpy(this->SoHieuMB, _SoHieuMB, 16);
    this->SoHieuMB[16] = '\0';
    // this->SoHieuMB = SoHieuMB;
    strcpy(this->LoaiMB, LoaiMB);
    this->SoDay = SoDay;
    this->SoDong = SoDong;
    SoLuotTHCB = 0;
}

void MayBay::setSoHieuMB(const char *SoHieuMB)
{

    strncpy(this->SoHieuMB, SoHieuMB, 16);
    this->SoHieuMB[16] = '\0';
    // strcpy(this->SoHieuMB, SoHieuMB);
}
char *MayBay::getSoHieuMB()
{
    return SoHieuMB;
}
void MayBay::setLoaiMB(const char *LoaiMB)
{
    strcpy(this->LoaiMB, LoaiMB);
}
char *MayBay::getLoaiMB()
{
    return LoaiMB;
}
void MayBay::setSoDay(int SoDay)
{
    this->SoDay = SoDay;
}
int MayBay::getSoDay()
{
    return SoDay;
}
void MayBay::setSoDong(int SoDong)
{
    this->SoDong = SoDong;
}
int MayBay::getSoDong()
{
    return SoDong;
}
int MayBay::getSoCho()
{
    return SoDay * SoDong;
}

void MayBay::show_MB()
{
    cout << getSoHieuMB() << " " << getLoaiMB() << " " << getSoDay() << " " << getSoDong() << endl;
}
bool MayBay::Kiemtrasocho(int socho)
{
    return socho >= 20;
}
string inttostring(int x)
{
    string p = "";
    while (x > 0)
    {

        int res = x % 10;
        p = char(res + 48) + p;
        x = x / 10;
    }
    return p;
}
void MayBay::DSChoNgoi()
{
    string p;
    string a[SoDay][SoDong];
    for (int i = 0; i < SoDay; i++)
    {
        p = char(i + 65);

        for (int j = 0; j < SoDong; j++)
        {
            string temp = p;
            if (j <= 8)
            {
                p = p + char(48);
            }
            p = p + inttostring(j + 1);

            a[i][j] = p;
            p = temp;
            // cout<<p<<endl;
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void MayBay::TangSLTHCB()
{
    this->SoLuotTHCB++;
}

int MayBay::getSoLuotBay()
{
    return this->SoLuotTHCB;
}

MayBay::~MayBay() {}
DSMB::DSMB()
{
}
// void DSMB::setsize(int size){
//     this->size=size;
// }
int DSMB::getsize()
{
    return size;
}

void DSMB::getDSMB()
{
    for (int i = 0; i < size; i++)
    {
        data[i]->show_MB();
    }
};
bool DSMB::Is_Empty()
{
    return (size == 0 ? true : false);
}

bool DSMB::Is_Full()
{
    return (size == MAXMB ? true : false);
}

MayBay *DSMB::New_MB(MayBay *maybay)
{
    MayBay *p = new MayBay;
    p = maybay;
    return p;
}

void DSMB::Insert_MB(MayBay *maybay)
{
    if (Is_Full()==true)
        return;
    data[size] = New_MB(maybay);
    size++;
}
void DSMB::Delete_MB(int index)
{
    delete data[index];
    for (int i = index; i < size - 1; i++)
    {
        data[index] = data[i + 1];
    }
    size--; //
}
int DSMB::Find_MB(const char *SoHieuMB) // Hàm tìm kiếm thì khi nhập index thì có điều kiện phải thoả DS.getsize()<=n-1 && >=0
{
    for (int i = 0; i < this->size; i++)
    {
        if (*this->data[i]->getSoHieuMB() == *SoHieuMB)
            return i;
    }
    return -1;
}
void DSMB::Delete_DSMB()
{
    for (int i = 0; i < size; i++)
    {
        delete data[i];
    }
}
MayBay *DSMB::getMB(int index)
{
    return data[index];
}
DSMB::~DSMB() {}
