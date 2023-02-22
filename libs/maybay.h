#pragma once
#include "header.h"
#define MAXMB 300

class MAYBAY //@brief MayBay @note abc
{
private:
    char SOHIEUMB[16];
    char LOAIMB[41];
    int SODAY;
    int SODONG;
public:
    MAYBAY(char _SOHIEUMB[16],char _LOAIMB[41], int _SODAY,int _SODONG);
    void setSOHIEUMB(char SOHIEUMB);
    char getSOHIEUMB();
    void setLOAIMB(char LOAIMB);
    char getLOAIMB();
    void setSODAY(int SODAY);
    int getSODAY();
    void setSODONG(int SODONG);
    int getSODONG();
    ~MAYBAY();

};

MAYBAY::MAYBAY(char _SOHIEUMB[16],char _LOAIMB[41], int _SODAY,int _SODONG)
{
    this->SOHIEUMB = _SOHIEUMB; 
    this->LOAIMB = _LOAIMB;
    this->SODAY = _SODAY;
    this->SODONG = _SODONG;
}



void MAYBAY::setSOHIEUMB(char SOHIEUMB)
{
    this->SOHIEUMB=SOHIEUMB;
}
char MAYBAY::getSOHIEUMB()
{
    return SOHIEUMB;
}
void MAYBAY::setLOAIMB(char LOAIMB)
{
    this->LOAIMB=LOAIMB;
}
char MAYBAY::getLOAIMB()
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





{
}

typedef struct MAYBAY MB;
struct listMB
{
    int n;
    MayBay *nodes[MAXMB];
};
typedef struct listMB LISTMB;
<<<<<<< HEAD
=======

struct Ve
{
    char ViTriNgoi[5];
    char CMND[11];
};
>>>>>>> 1b529a247d788913221165da0f226152d3386c9c
