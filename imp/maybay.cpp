#include "../header/maybay.h"
#include <sstream>

MayBay::MayBay() {
    strcpy(SoHieuMB, "");

    strcpy(LoaiMB, "");
    SoDay=0;
    SoDong=0;
    SoLuotTHCB = 0;
}
MayBay::MayBay(const char *_SoHieuMB, const char *LoaiMB, int SoDay, int SoDong)
{
    strncpy(this->SoHieuMB, _SoHieuMB, 16);
    this->SoHieuMB[16] = '\0';
    // this->SoHieuMB = SoHieuMB;
    strncpy(this->LoaiMB, LoaiMB, 41);
    this->LoaiMB[41] = '\0';
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
    return this->SoHieuMB;
}
void MayBay::setLoaiMB(const char *LoaiMB)
{
    strncpy(this->LoaiMB, LoaiMB, 41);
    this->LoaiMB[41] = '\0';
}
char *MayBay::getLoaiMB()
{
    return this->LoaiMB;
}
void MayBay::setSoDay(int SoDay)
{
    this->SoDay = SoDay;
}
int MayBay::getSoDay()
{
    return this->SoDay;
}
void MayBay::setSoDong(int SoDong)
{
    this->SoDong = SoDong;
}
int MayBay::getSoDong()
{
    return SoDong;//
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
    size = 0;
}

int DSMB::getsize()
{
    return this->size;
}

void DSMB::getDSMB()
{
    for (int i = 0; i < this->size; i++)
    {
        data[i]->show_MB();
    }
};
bool DSMB::Is_Empty()
{
    return size == 0;
}

bool DSMB::Is_Full()
{
    return size == MAXMB;
}

// MayBay *DSMB::New_MB(MayBay *maybay)
// {
//     MayBay *p = new MayBay;
//     p = maybay;
//     return p;
// }

void DSMB::Insert_MB(MayBay *maybay)
{
    if (Is_Full()==true)
        return;
    data[size] = maybay;
    size++;
}
void DSMB::Delete_MB(int index)
{
    delete data[index];
    for (int i = index; i < this->size - 1; i++)
    {
        data[index] = data[i + 1];
    }
    this->size--; //
}
int DSMB::Find_MB(char *_SoHieuMB) // Hàm tìm kiếm thì khi nhập index thì có điều kiện phải thoả DS.getsize()<=n-1 && >=0
{
    for (int i = 0; i < this->size; i++)
    {
        if (*this->data[i]->getSoHieuMB() == *_SoHieuMB)
            return i;
    }
    return -1;
}
int DSMB::vitri(const char *a,const char *b){
    int d=-1;
    if(strstr(a,b)!=NULL)
    d=strlen(a)-strlen(strstr(a,b));
    return d;
}
//khi tìm và lấy cả danh sách máy bay thì stringsearch không được là == ""
DSMB* DSMB::Find_DSMB(const char *String_Search){
    DSMB *dsmb=new DSMB();
    for(int j=0;j<size;j++)
    {
        if(vitri(data[j]->getSoHieuMB(),String_Search) ==0 )
        {
            dsmb->Insert_MB(getMB(j));
        }
        
    }
    if(dsmb->getsize()==0) return NULL;
    return dsmb;
}

void DSMB::Delete_DSMB()
{
    for (int i = 0; i < this->size; i++)
    {
        delete data[i];
    }
}
MayBay *DSMB::getMB(int index)
{
    return data[index];
}
void DSMB::ReadFromFile(ifstream &file){
    if(file.is_open())
    {
        std::string sohieumb, loaimb, soday, sodong;
        std::string line = "";
        while(std::getline(file, line)){
            std::stringstream s(line);
            std::getline(s, sohieumb, '|');
            getline(s, loaimb, '|');
            getline(s, soday, '|');
            getline(s, sodong, '|');
            Insert_MB(new MayBay(sohieumb.c_str(), loaimb.c_str(), stoi(soday), stoi(sodong)));
        }
    }
    else cout<<"Error"<<endl;

}
void DSMB::WritetoFile(ofstream &file){
    if (file.is_open())
    {
        for(int i=0;i<size;i++){
            file<<data[i]->getSoHieuMB()<<"|"<<data[i]->getLoaiMB()<<"|"<<data[i]->getSoDay()<<"|"<<data[i]->getSoDong()<<"|"<<"\n";
        }
    }
    else
    {
        cout << "Error";
    }
    file.close();
}
DSMB::~DSMB() {
    for(int i = 0; i<size; i++){
        delete data[i];
    }
}