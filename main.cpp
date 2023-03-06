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
     Date **date;
     date = new Date *[10];
     for (int i = 0; i < 10; i++)
     {
          date[i] = new Date(8, 20, 15 + i, 3, 2023);
     }
     ChuyenBay **cb;
     cb = new ChuyenBay *[10];
     for (int i = 0; i < 10; i++)
     {
          cb[i] = new ChuyenBay("MB" + i, "Lien Khuong", date[i], mb[i]);
     }

     cb[0]->setDSVeMB();
     cb[0]->showDSVe();

     system("pause");
     return 0;
}