#pragma once

#include "header.h"
#include "maybay.h"

class VeMayBay
{
private:
	string idVe;
	string cmnd;

public:
	VeMayBay();
	VeMayBay(string cmnd);
	void setIDVe(string id);
	string getIDVe();
	void setHanhKhach(string cmnd);
	string getHanhKhach();
};

class DsVeMayBay
{
private:
	VeMayBay *dsVeMB;
	int soVeToiDa;
	int soVeDaDat;

public:
	DsVeMayBay();

	void setSoVeToiDa(int soVeToiDa);
	void setSoVeDaDat(int soVeDaDat);

	int getSoVeToiDa();
	int getSoVeDaDat();
	int getSoVeConLai();
	VeMayBay *getDSVeMB();
	void setDSVe(MayBay *mayBay);
	void setVe(VeMayBay ve, int pos);
	VeMayBay getVe(int index);
	void deleteVe(int index);
	void deleteDsVe();
};
