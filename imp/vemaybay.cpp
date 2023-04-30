#include "../header/vemaybay.h"
// hàm của DSVe

VeMayBay::VeMayBay() {
  IDVe = "A00";
  CMND = "\0";
  // TrangThai = true; // true là chưa đặt
  //                   // false là đặt vé
}

VeMayBay::VeMayBay(string CMND) { this->CMND = CMND; }

void VeMayBay::setIDVe(string ID) { this->IDVe = ID; }

string VeMayBay::getIDVe() { return this->IDVe; }

void VeMayBay::setHanhKhach(string CMND) { this->CMND = CMND; }

string VeMayBay::getHanhKhach() { return this->CMND; }

// void VeMayBay::setTrangThai(bool TrangThai) { this->TrangThai = TrangThai; }

// bool VeMayBay::getTrangThai() { return this->TrangThai; }

// ham DSvemaybay
DSVeMayBay::DSVeMayBay() {
  // DSVeMB=new VeMayBay[SoVeToiDa];
  this->SoVeToiDa = 0;
  this->SoVeDaDat = 0;
}

void DSVeMayBay::setSoVeToiDa(int SoVeToiDa) { this->SoVeToiDa = SoVeToiDa; }

void DSVeMayBay::setSoVeDaDat(int SoVeDaDat) { this->SoVeDaDat = SoVeDaDat; }

int DSVeMayBay::getSoVeToiDa() { return SoVeToiDa; }

int DSVeMayBay::getSoVeDaDat() { return SoVeDaDat; }

int DSVeMayBay::getSoVeConLai() { return SoVeToiDa - SoVeDaDat; }

VeMayBay *DSVeMayBay::getDSVeMB() { return DSVeMB; }
void DSVeMayBay::setDSVe(MayBay *MB) {
  int SDay, SDong;
  SDay = MB->getSoDay();
  SDong = MB->getSoDong();
  SoVeToiDa = SDay * SDong;
  DSVeMB = new VeMayBay[SoVeToiDa];
  for (int i = 0; i < SDay; i++) {
    for (int j = 0; j < SDong; j++) {
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

void DSVeMayBay::setVe(VeMayBay Ve, int pos) { DSVeMB[pos] = Ve; }
VeMayBay DSVeMayBay::getVe(int index) { return DSVeMB[index]; }

DSVeMayBay::~DSVeMayBay() {}