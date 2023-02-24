#include "libs/libs.h"
#include <windows.h>

using namespace std;

int main()
{
     std::cout << "Hello, world!" << std::endl;

     string idVe = "A01", noiden = "Lien Khuong",
            cmnd = "251336020", ho = "Pham Bui Nam", ten = "Phuong";
     char IDChuyenBay[15] = "MB15", sohieuMB[35] = "MH370",
          loaiMB[35] = "boing177";
     Date *ngayBay = new Date(20, 10, 30, 3, 2023);
     MayBay *mBay = new MayBay(sohieuMB, loaiMB, 5, 5);
     HanhKhach *hk = new HanhKhach(cmnd, ho, ten, 1);
     VeMayBay *veBay = new VeMayBay("A12", hk);
     ChuyenBay *cBay = new ChuyenBay(IDChuyenBay, noiden, ngayBay, mBay);

     cout << "Thong tin chuyen bay: " << endl;
     cout << "   ID chuyen bay: " << cBay->getMaCB() << endl;
     cout << "   Dich den: " << cBay->getNoiDen() << endl;
     cout << "   Ngay bay: ";
     cBay->getNgayGio()->showTG();
     cout << endl;
     cout << "May bay: " << endl;
     cout << "   So hieu MB: " << cBay->getMayBay().getSoHieuMB() << endl;
     cout << "   Loai MB: " << cBay->getMayBay().getLoaiMB() << endl;
     cout << "   So day / So dong: " << cBay->getMayBay().getSoDay()
          << " / " << cBay->getMayBay().getSoDong() << endl;
     cout << "Thong tin ve: " << endl;
     cout << "   Ma so ve: " << veBay->getIDVe() << endl;
     cout << "Thong tin khach hang dat ve: " << endl;
     cout << "   Ho va Ten: " << veBay->getHanhKhach()->getHo() << " "
          << veBay->getHanhKhach()->getTen() << endl;
     cout << "   CMND: " << veBay->getHanhKhach()->getCmnd() << endl;
     cout << "   Phai: " << ((veBay->getHanhKhach()->getPhai() == 1) ? "Nam" : "Nu") << endl;

     system("pause");
     return 0;
}