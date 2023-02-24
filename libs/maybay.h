#pragma once
#include "header.h"
#include <string>
#define MAXMB 300

class MayBay 
{
private:
    char *SoHieuMB; // @note xây dựng hàm chỉ cho phép nhập 16 kí tự
    char *LoaiMB;   // 41 kí tự
    int SoDay;
    int SoDong;

public:
    MayBay();
    MayBay(char *SoHieuMB, char *LoaiMB, int SoDay, int SoDong);
    void setSoHieuMB(char *SoHieuMB);
    char* getSoHieuMB();
    void setLoaiMB(char *LoaiMB);
    char* getLoaiMB();
    void setSoDay(int SoDay);
    int getSoDay();
    void setSoDong(int SoDong);
    int getSoDong();
    int getSoCho();
    void show_MB();
    bool Kiemtrasocho(int socho);
    ~MayBay();
};
MayBay::MayBay() {}
MayBay::MayBay(char *SoHieuMB, char *LoaiMB, int SoDay, int SoDong)
{
    this->SoHieuMB = SoHieuMB;
    this->LoaiMB = LoaiMB;
    this->SoDay = SoDay;
    this->SoDong = SoDong;
}

void MayBay::setSoHieuMB(char *SoHieuMB)
{
    this->SoHieuMB = SoHieuMB;
}
char* MayBay::getSoHieuMB()
{
    return SoHieuMB;
}
void MayBay::setLoaiMB(char *LoaiMB)
{
    this->LoaiMB = LoaiMB;
}
char* MayBay::getLoaiMB()
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
int MayBay::getSoCho(){
    return SoDay*SoDong;
}

void MayBay::show_MB(){
    cout<<getSoHieuMB()<<" "<<getLoaiMB()<<" "<<getSoDay()<<" "<<getSoDong()<<endl;
}
bool MayBay::Kiemtrasocho(int socho){
    return socho>=20;
}

// typedef struct MAYBAY MB;
// struct listMB
// {
//     int n;
//     MAYBAY *nodes[MAXMB];
// };
// typedef struct listMB LISTMB;




// Danh sách con trỏ của máy bay
//======================================================================
class DSMB
{
private:
    int size=0;
    MayBay *data[MAXMB];
public:
    DSMB();
    // void setsize(int size);
    // int getsize();
    void getDSMB();
    bool Is_Empty(DSMB &DS);
    bool Is_Full(DSMB &DS);
    MayBay* New_MB(MayBay &maybay);
    void Insert_MB(DSMB &DS, MayBay &maybay);
    void Delete_MB(DSMB &DS, int index);
    int Find_MB(DSMB &DS,char *SoHieuMB);
    void Delete_DSMB(DSMB &DS );
};
DSMB::DSMB(){
}
// void DSMB::setsize(int size){
//     this->size=size;
// }
// int DSMB::getsize(){
//     return size;
// }

void DSMB::getDSMB(){
    for(int i=0;i<getsize();i++){
        data[i]->show_MB();
    }
};
bool DSMB::Is_Empty(DSMB &DS) {
	return (DS.size == 0 ? true : false);
}

bool DSMB::Is_Full(DSMB &DS) {
	return (DS.size >= MAXMB ? true : false);
}

MayBay* DSMB:: New_MB(MayBay &maybay) {
	MayBay *p = new MayBay;
	*p = maybay;
	return p;
}

void DSMB::Insert_MB(DSMB &DS, MayBay &maybay) {
	if (DS.size == MAXMB)
		return;
	DS.data[DS.size] = New_MB(maybay);
	DS.size++;
}
void DSMB::Delete_MB(DSMB &DS, int index){
    delete DS.data[index];
    for(int i=index;i<DS.size-1;i++){
        DS.data[index]=DS.data[i+1];
    }
    DS.size--;
}
int DSMB::Find_MB(DSMB &DS,char *SoHieuMB){
    for(int i=0;i<DS.size;i++){
        if(DS.data[i]->getSoHieuMB()==SoHieuMB)
            return i+1;
    }
    return -1;
}
void DSMB::Delete_DSMB(DSMB &DS ){
    for(int i=0;i<DS.size;i++){
        delete DS.data[i];
    }
}

