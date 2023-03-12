#include "libs/libs.h"
#include "windows.h"

using namespace std;

int main()
{
     MayBay **mb;
     mb = new MayBay *[10];
     for (int i = 0; i < 10; i++)
     {
          mb[i] = new MayBay("MB" + i, "boing" + i, 4 + i, 20 - i);
     }
     Date *date = new Date[10];
     for (int i = 0; i < 10; i++)
     {
          date[i] = Date(8, 20, 15 + i, 3, 2023);
     }
     ChuyenBay **cb;
     cb = new ChuyenBay *[10];
     for (int i = 0; i < 10; i++)
     {
          cb[i] = new ChuyenBay("MB" + i, "Lien Khuong", date[i], mb[i]);
     }
     ChuyenBay *cbp = new ChuyenBay("MH2", "Ha Noi", date[0], mb[0]);

     cb[0]->setDSVeMB();
     cb[0]->showDSVeTrong();
     cb[0]->ThucHienCB();
     cbp->ThucHienCB();
     cout << endl
          << "SLB: " << mb[0]->getSoLuotBay() << endl;
     system("pause");
     return 0;
}