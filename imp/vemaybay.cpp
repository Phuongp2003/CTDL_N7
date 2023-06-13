#include "../header/vemaybay.h"

VeMayBay::VeMayBay()
{
  idVe = "A00";
  cmnd = "\0";
}

VeMayBay::VeMayBay(string cmnd) { this->cmnd = cmnd; }

void VeMayBay::setIDVe(string idVe) { this->idVe = idVe; }

string VeMayBay::getIDVe() { return this->idVe; }

void VeMayBay::setHanhKhach(string cmnd) { this->cmnd = cmnd; }

string VeMayBay::getHanhKhach() { return this->cmnd; }

DsVeMayBay::DsVeMayBay()
{
  this->soVeToiDa = 0;
  this->soVeDaDat = 0;
}

void DsVeMayBay::setSoVeToiDa(int soVeToiDa) { this->soVeToiDa = soVeToiDa; }

void DsVeMayBay::setSoVeDaDat(int soVeDaDat) { this->soVeDaDat = soVeDaDat; }

int DsVeMayBay::getSoVeToiDa() { return soVeToiDa; }

int DsVeMayBay::getSoVeConLai() { return soVeToiDa - soVeDaDat; }

int DsVeMayBay::getSoVeDaDat() { return soVeDaDat; }

VeMayBay *DsVeMayBay::getDSVeMB() { return dsVeMB; }

void DsVeMayBay::setDSVe(MayBay *mayBay)
{
  int soDay, soDong;
  soDay = mayBay->getSoDay();
  soDong = mayBay->getSoDong();
  soVeToiDa = soDay * soDong;
  dsVeMB = new VeMayBay[soVeToiDa];
  for (int i = 0; i < soDay; i++)
  {
    for (int j = 0; j < soDong; j++)
    {
      string tmpStr;
      tmpStr += idChu[i];
      tmpStr += idSo[(j + 1) / 10];
      tmpStr += idSo[(j + 1) % 10];
      tmpStr += '\0';
      // tmp_str = tmp_str;
      dsVeMB[i * soDong + j].setIDVe(tmpStr);
    }
  }
}

void DsVeMayBay::setVe(VeMayBay veMB, int pos) { dsVeMB[pos] = veMB; }

VeMayBay DsVeMayBay::getVe(int index) { return dsVeMB[index]; }

void DsVeMayBay::deleteVe(int index)
{
  dsVeMB[index].setHanhKhach("");
  soVeDaDat--;
}
void DsVeMayBay::deleteDsVe()
{
  delete[] dsVeMB;
}
