#include "../header/vemaybay.h"
// hàm của DSVe

VeMayBay::VeMayBay()
{
    IDVe = "A00";
    CMND = "\0";
    TrangThai = true;
}

VeMayBay::VeMayBay(string IDVe, string CMND)
{
    this->IDVe = IDVe;
    this->CMND = CMND;
}

void VeMayBay::setIDVe(string ID)
{
    this->IDVe = ID;
}

string VeMayBay::getIDVe()
{
    return this->IDVe;
}

void VeMayBay::setHanhKhach(string CMND)
{
    this->CMND = CMND;
}

string VeMayBay::getHanhKhach()
{
    return this->CMND;
}

void VeMayBay::setTrangThai(bool TrangThai)
{
    this->TrangThai = TrangThai;
}

bool VeMayBay::getTrangThai()
{
    return this->TrangThai;
}
// ham DSvemaybay
DSVeMayBay::DSVeMayBay()
{
    this->SoVeToiDa = 0;
    this->SoVeDaDat = 0;
}

void DSVeMayBay::setSoVeToiDa(int SoVeToiDa)
{
    this->SoVeToiDa = SoVeToiDa;
}
int DSVeMayBay::getSoVeToiDa()
{
    return SoVeToiDa;
}

VeMayBay *DSVeMayBay::getDSVeMB()
{
    return DSVeMB;
}
void DSVeMayBay::setDSVe(MayBay *MB)
{
    int SDay, SDong;
    SDay = MB->getSoDay();
    SDong = MB->getSoDong();
    SoVeToiDa = SDay * SDong;
    DSVeMB = new VeMayBay[SoVeToiDa];
    for (int i = 0; i < SDay; i++)
    {
        for (int j = 0; j < SDong; j++)
        {
            string tmp_str;
            tmp_str += IDChu[i];
            tmp_str += IDSo[(j + 1) / 10];
            tmp_str += IDSo[(j + 1) % 10];
            tmp_str += '\0';
            // tmp_str = tmp_str;
            DSVeMB[i * SDong + j].setIDVe(tmp_str);
        }
    }
}

DSVeMayBay::~DSVeMayBay() {}