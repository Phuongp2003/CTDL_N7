#include "../header/maybay.h"

MayBay::MayBay()
{
  strcpy(soHieuMB, "");
  strcpy(loaiMB, "");
  soDay = 0;
  soDong = 0;
  soLuotThucHienCB = 0;
  isUsed = false;
}

MayBay::MayBay(const char *soHieuMB, const char *loaiMB, int soDay,
               int soDong)
{
  strcpy(this->soHieuMB, soHieuMB);
  strcpy(this->loaiMB, loaiMB);
  this->soDay = soDay;
  this->soDong = soDong;
  soLuotThucHienCB = 0;
  isUsed = false;
}

MayBay::MayBay(const char *soHieuMB, const char *loaiMB, int soDay,
               int soDong, int soLuotThucHienCB, bool isUsed)
{
  strcpy(this->soHieuMB, soHieuMB);
  strcpy(this->loaiMB, loaiMB);
  this->soDay = soDay;
  this->soDong = soDong;
  this->soLuotThucHienCB = soLuotThucHienCB;
  this->isUsed = isUsed;
}

void MayBay::setSoHieuMB(const char *soHieuMB)
{

  strcpy(this->soHieuMB, soHieuMB);
}

char *MayBay::getSoHieuMB() { return this->soHieuMB; }

void MayBay::setLoaiMB(const char *loaiMB)
{
  strcpy(this->loaiMB, loaiMB);
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

void MayBay::tangSoLuotThucHienCB() { this->soLuotThucHienCB++; }

int MayBay::getSoLuotBay() { return this->soLuotThucHienCB; }

void MayBay::setUsed()
{
  this->isUsed = true;
}

bool MayBay::inUsed() { return isUsed; }

DsMayBay::DsMayBay() { size = 0; }

int DsMayBay::getSize() { return this->size; }

bool DsMayBay::isEmpty() { return size == 0; }

bool DsMayBay::isFull() { return size == MAXMB; }

void DsMayBay::insertMB(MayBay *maybay)
{
  if (isFull() == true)
    return;
  data[size] = maybay;
  size++;
}
void DsMayBay::deleteMB(int index)
{
  if (isEmpty() == true)
    return;
  delete data[index];
  for (int i = index; i < this->size - 1; i++)
  {
    data[i] = data[i + 1];
  }
  this->size--;
}

int DsMayBay::findPosMB(const char *soHieuMB)
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

void DsMayBay::deleteDsMB()
{
  for (int i = 0; i < MAXMB; i++)
  {
    if (i < size)
    {
      if (data[i] != NULL)
        cout << "Delete " << data[i]->getSoHieuMB() << "|\n";
      else
        cout << "Delete "
             << "NULL pointer"
             << "|\n";
      delete data[i];
    }
    data[i] = nullptr;
  }
  this->size = 0;
}

MayBay *DsMayBay::getMB(int index) { return data[index]; }

void DsMayBay::readFromFile()
{
  ifstream file("../data/dataMB.txt", ios::in);
  if (file.is_open())
  {
    deleteDsMB();
    this->size = 0;
    string soHieuMB, loaiMB, soDay, soDong, soLuotThucHienCB, isUsed;
    string line = "";
    bool used;
    while (getline(file, line))
    {
      stringstream s(line);
      getline(s, soHieuMB, '|');
      getline(s, loaiMB, '|');
      getline(s, soDay, '|');
      getline(s, soDong, '|');
      getline(s, soLuotThucHienCB, '|');
      getline(s, isUsed, '|');
      used = (isUsed == "1") ? true : false;
      insertMB(new MayBay(soHieuMB.c_str(), loaiMB.c_str(), stoi(soDay),
                          stoi(soDong), stoi(soLuotThucHienCB), used));
    }
    file.close();

    cout << "Đọc file máy bay thành công!" << endl;
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

void DsMayBay::writetoFile()
{
  ofstream file("../data/dataMB.txt", ios::out | ios::trunc);
  if (file.is_open())
  {
    for (int i = 0; i < size; i++)
    {
      file << data[i]->getSoHieuMB() << "|" << data[i]->getLoaiMB() << "|"
           << data[i]->getSoDay() << "|" << data[i]->getSoDong() << "|"
           << data[i]->getSoLuotBay() << "|" << data[i]->inUsed() << "|"
           << "\n";
    }
    cout << "Xuất file MB thành công!" << endl;
  }
  else
  {
    cout << "Error";
  }
  file.close();
}

void DsMayBay::writetoFileWhenAdd()
{
  ofstream file("../data/dataMB.txt", ios::out | ios::app);
  if (file.is_open())
  {
    file << data[size - 1]->getSoHieuMB() << "|" << data[size - 1]->getLoaiMB() << "|"
         << data[size - 1]->getSoDay() << "|" << data[size - 1]->getSoDong() << "|"
         << data[size - 1]->getSoLuotBay() << "|" << data[size - 1]->inUsed() << "|"
         << "\n";
    cout << "Viết máy bay " << data[size - 1]->getSoHieuMB() << " vào file!" << endl;
  }
  else
  {
    cout << "Error";
  }
  file.close();
}

bool DsMayBay::planeMatch(const char *soHieuMB, const char *other)
{
  if (other == NULL)
    return false;

  if ((findMB(soHieuMB)->getSoDay() == findMB(other)->getSoDay()) &&
      (findMB(soHieuMB)->getSoDong() == findMB(other)->getSoDong()))
    return true;

  return false;
}
