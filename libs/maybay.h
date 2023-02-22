#pragma once
#include "header.h"
#include <cstring>
#define MAXMB 300

class MAYBAY //@brief MayBay @note abc
{
private:
    string SOHIEUMB; // @note xây dựng hàm chỉ cho phép nhập 16 kí tự
    string LOAIMB;  // @note
    int SODAY;
    int SODONG;
public:
    MAYBAY();
    MAYBAY(string SOHIEUMB,string LOAIMB, int SODAY,int SODONG);
    void setSOHIEUMB(string SOHIEUMB);
    string getSOHIEUMB();
    void setLOAIMB(string LOAIMB);
    string getLOAIMB();
    void setSODAY(int SODAY);
    int getSODAY();
    void setSODONG(int SODONG);
    int getSODONG();
    ~MAYBAY();

};

MAYBAY::MAYBAY(string SOHIEUMB,string LOAIMB, int SODAY,int SODONG)
{
    this->SOHIEUMB = SOHIEUMB;
    this->LOAIMB = LOAIMB;
    this->SODAY = SODAY;
    this->SODONG = SODONG;
}



void MAYBAY::setSOHIEUMB(string SOHIEUMB)
{
    this->SOHIEUMB=SOHIEUMB;
}
string MAYBAY::getSOHIEUMB()
{
    return SOHIEUMB;
}
void MAYBAY::setLOAIMB(string LOAIMB)
{
    this->LOAIMB=LOAIMB;
}
string MAYBAY::getLOAIMB()
{
    return LOAIMB;
}
void MAYBAY::setSODAY(int SODAY)
{
    this->SODAY=SODAY;
}
int MAYBAY::getSODAY()
{
    return SODAY;
}
void MAYBAY::setSODONG(int SODONG)
{
    this->SODONG=SODONG;
}
int MAYBAY:: getSODONG()
{
    return SODONG;
}



// typedef struct MAYBAY MB;
// struct listMB
// {
//     int n;
//     MAYBAY *nodes[MAXMB];
// };
// typedef struct listMB LISTMB;
