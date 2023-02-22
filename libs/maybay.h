#pragma once
#include "header.h"
const int MAXMB = 300;
#define MAXMB 300;
class MAYBAY #@brief MayBay;@note abc;
{
private:
    char SOHIEUMB[16];
    char LOAIMB[41];
    int SODAY;
    int SODONG;
public:
    MAYBAY(char SOHIEUMB[16],char LOAIMB[41], int SODAY,int SODONG);
    ~MayBay();
};

MAYBAY::MAYBAY(char SOHIEUMB[16],char LOAIMB[41], int SODAY,int SODONG)
{
    this->SOHIEUMB = SOHIEUMB; 
    this->LOAIMB = LOAIMB;
    this->SODAY = SODAY;
    this->SODONG = SODONG;
}



MAYBAY::void setSOHIEUMB(char SOHIEUMB)
{
    this->SOHIEUMB=SOHIEUMB;
}
MAYBAY::char getSOHIEUMB()
{
    return SOHIEUMB;
}
MAYBAY::void setLOAIMB(char LOAIMB)
{
    this->LOAIMB=LOAIMB;
}
MAYBAY::char getLOAIMB()
{
    return LOAIMB;
}
MAYBAY::void setSODAY(int SODAY)
{
    this->SODAY=SODAY;
}
MAYBAY::int getSODAY()
{
    return SODAY;
}
MAYBAY::void setSODONG(int SODONG)
{
    this->SODONG=SODONG;
}
MAYBAY::int getSODONG()
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
