#include "../header/maybay.h"
#include <sstream>

MayBay::MayBay()
{
  strcpy(soHieuMB, "");

  strcpy(loaiMB, "");
  soDay = 0;
  soDong = 0;
  soLuotThucHienCB = 0;
}

MayBay::MayBay(const char *soHieuMB, const char *loaiMB, int soDay,
               int soDong)
{
  strncpy(this->soHieuMB, soHieuMB, 16);
  this->soHieuMB[16] = '\0';
  // this->SoHieuMB = SoHieuMB;
  strncpy(this->loaiMB, loaiMB, 41);
  this->loaiMB[41] = '\0';
  this->soDay = soDay;
  this->soDong = soDong;
  soLuotThucHienCB = 0;
}

MayBay::MayBay(const char *soHieuMB, const char *loaiMB, int soDay,
               int soDong, int soLuotThucHienCB)
{
  strncpy(this->soHieuMB, soHieuMB, 16);
  this->soHieuMB[16] = '\0';
  // this->SoHieuMB = SoHieuMB;
  strncpy(this->loaiMB, loaiMB, 41);
  this->loaiMB[41] = '\0';
  this->soDay = soDay;
  this->soDong = soDong;
  this->soLuotThucHienCB = soLuotThucHienCB;
}

void MayBay::setSoHieuMB(const char *soHieuMB)
{

  strncpy(this->soHieuMB, soHieuMB, 16);
  this->soHieuMB[16] = '\0';
  // strcpy(this->SoHieuMB, soHieuMB);
}

char *MayBay::getSoHieuMB() { return this->soHieuMB; }

void MayBay::setLoaiMB(const char *loaiMB)
{
  strncpy(this->loaiMB, loaiMB, 41);
  this->loaiMB[41] = '\0';
}

char *MayBay::getLoaiMB() { return this->loaiMB; }

void MayBay::setSoDay(int soDay) { this->soDay = soDay; }

int MayBay::getSoDay() { return this->soDay; }

void MayBay::setSoDong(int soDong) { this->soDong = soDong; }

int MayBay::getSoDong()
{
  return this->soDong; //
}

int MayBay::getSoCho()
{
  return this->soDay * this->soDong;
}

void MayBay::showMB()
{
  cout << getSoHieuMB() << " " << getLoaiMB() << " " << getSoDay() << " "
       << getSoDong() << endl;
}

bool MayBay::kiemTraSoCho(int soCho) { return soCho >= 20; }

string intToString(int x)
{
  string p = "";
  while (x > 0)
  {

    int res = x % 10;
    p = char(res + 48) + p;
    x = x / 10;
  }
  return p;
}
void MayBay::dsChoNgoi()
{
  string p;
  string a[soDay][soDong];
  for (int i = 0; i < soDay; i++)
  {
    p = char(i + 65);

    for (int j = 0; j < soDong; j++)
    {
      string temp = p;
      if (j <= 8)
      {
        p = p + char(48);
      }
      p = p + intToString(j + 1);

      a[i][j] = p;
      p = temp;
      // cout<<p<<endl;
      cout << a[i][j] << " ";
    }
    cout << endl;
  }
}

void MayBay::tangSoLuotThucHienCB() { this->soLuotThucHienCB++; }

int MayBay::getSoLuotBay() { return this->soLuotThucHienCB; }

MayBay::~MayBay() {}

DsMayBay::DsMayBay() { size = 0; }

int DsMayBay::getSize() { return this->size; }

void DsMayBay::getDsMayBay()
{
  for (int i = 0; i < this->size; i++)
  {
    data[i]->showMB();
  }
};
bool DsMayBay::isEmpty() { return size == 0; }

bool DsMayBay::isFull() { return size == MAXMB; }

// MayBay *DsMayBay::New_MB(MayBay *maybay)
// {
//     MayBay *p = new MayBay;
//     p = maybay;
//     return p;
// }

void DsMayBay::insertMB(MayBay *maybay)
{
  if (isFull() == true)
    return;
  data[size] = maybay;
  size++;
}
void DsMayBay::deleteMB(int index)
{
  delete data[index];
  for (int i = index; i < this->size - 1; i++)
  {
    data[i] = data[i + 1];
  }
  this->size--; //
}

int DsMayBay::findPosMB(
    const char *soHieuMB) // Hàm tìm kiếm thì khi nhập index thì có điều kiện
                          // phải thoả DS.getsize()<=n-1 && >=0
{
  for (int i = 0; i < this->size; i++)
  {
    if (strcmp(this->data[i]->getSoHieuMB(), soHieuMB) == 0)
      return i;
  }
  return -1;
}

MayBay *DsMayBay::findMB(const char *soHieuMB)
{
  for (int i = 0; i < this->size; i++)
  {
    if (strcmp(this->data[i]->getSoHieuMB(), soHieuMB) == 0)
      return data[i];
  }
  return NULL;
}

int DsMayBay::viTri(const char *a, const char *b)
{
  int d = -1;
  if (strstr(a, b) != NULL)
    d = strlen(a) - strlen(strstr(a, b));
  return d;
}
// khi tìm và lấy cả danh sách máy bay thì stringsearch không được là == ""
// DsMayBay DsMayBay::findDsMB(const char *String_Search)
// {
//   DsMayBay *dsmb = new DsMayBay();
//   for (int j = 0; j < size; j++)
//   {
//     if (isGotStr(data[j]->getSoHieuMB(), String_Search))
//     {
//       dsmb->insertMB(getMB(j));
//     }
//   }
//   if (dsmb->getSize() == 0)
//   {
//     delete dsmb;
//     return *(new DsMayBay());
//   }
//   return *dsmb;
// }

void DsMayBay::deleteDsMB()
{
  for (int i = 0; i < this->size; i++)
  {
    delete data[i];
  }
  this->size = 0;
}

MayBay **DsMayBay::getMB() { return data; }

void DsMayBay::readFromFile(ifstream &file)
{
  if (file.is_open())
  {
    deleteDsMB();
    std::string soHieuMB, loaiMB, soDay, soDong, soLuotThucHienCB;
    std::string line = "";
    while (std::getline(file, line))
    {
      std::stringstream s(line);
      std::getline(s, soHieuMB, '|');
      getline(s, loaiMB, '|');
      getline(s, soDay, '|');
      getline(s, soDong, '|');
      getline(s, soLuotThucHienCB, '|');
      insertMB(new MayBay(soHieuMB.c_str(), loaiMB.c_str(), stoi(soDay),
                          stoi(soDong), stoi(soLuotThucHienCB)));
    }
    file.close();
  }
  else
    cout << "Error" << endl;
}

int *DsMayBay::sapXepThongKe()
{
  int *A = new int[size];
  for (int i = 0; i < size; i++)
  {
    A[i] = i;
  }

  int max, vitrimax;
  int i, j;
  for (i = 0; i < size - 1; i++)
  {
    max = data[A[i]]->getSoLuotBay();
    vitrimax = i;
    for (j = i + 1; j < size; j++)
      if (data[A[j]]->getSoLuotBay() > max)
      {
        max = data[A[j]]->getSoLuotBay();
        vitrimax = j;
      }
    swap(A[vitrimax], A[i]);
  }

  return A;
}

void DsMayBay::writetoFile(ofstream &file)
{
  if (file.is_open())
  {
    for (int i = 0; i < size; i++)
    {
      file << data[i]->getSoHieuMB() << "|" << data[i]->getLoaiMB() << "|"
           << data[i]->getSoDay() << "|" << data[i]->getSoDong() << "|"
           <<data[i]->getSoLuotBay()<<"|"
           << "\n";
    }
  }
  else
  {
    cout << "Error";
  }
  file.close();
}
DsMayBay::~DsMayBay()
{
  // for(int i = 0; i<size; i++){
  //     delete data[i];
  // }
}
