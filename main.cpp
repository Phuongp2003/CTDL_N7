#include "header/libs.h"
// #include "windows.h"

using namespace std;
int main()
{
     DSMB *DanhSachMB = new DSMB();
     MayBay **mb;
     mb = new MayBay *[10];
     mb[0] = new MayBay("MB01", "boing", 4, 20);
     DanhSachMB->Insert_MB(mb[0]);
     Date *date = new Date[10];
     for (int i = 0; i < 10; i++)
     {
          date[i] = Date(8, 20, 15 + i, 3, 2023);
     }
     ChuyenBay **cb;
     cb = new ChuyenBay *[10];
     cb[0] = new ChuyenBay("MH01", "Lien Khuong", date[0], "MB01");
     ChuyenBay *cbp = new ChuyenBay("MH2", "Ha Noi", date[0], "MB01");

     cb[0]->setDSVeMB(DanhSachMB);
     cb[0]->showDSVe();
     cb[0]->ThucHienCB(DanhSachMB);
     cbp->ThucHienCB(DanhSachMB);
     cout << endl
          << "SLB: " << mb[0]->getSoLuotBay() << endl;
     // system("pause");Segmentation fault
     InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "First Screen");
     CreateScreen();
     CloseWindow();
     return 0;
}