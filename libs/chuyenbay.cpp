#include "chuyenbay.h"
using namespace std;

// hàm của DSVe

VeMayBay::VeMayBay()
{
    IDVe = "A00";
}

VeMayBay::VeMayBay(string IDVe, HanhKhach *HanhKhachMuaVe)
{
    this->IDVe = IDVe;
    this->HanhKhachMuaVe = HanhKhachMuaVe;
}

void VeMayBay::setIDVe(string ID)
{
    this->IDVe = ID;
}

string VeMayBay::getIDVe()
{
    return this->IDVe;
}

void VeMayBay::setHanhKhach(HanhKhach *HanhKhachMuaVe)
{
    this->HanhKhachMuaVe = HanhKhachMuaVe;
}

HanhKhach *VeMayBay::getHanhKhach()
{
    return this->HanhKhachMuaVe;
}

// hàm của ChuyenBay

ChuyenBay::ChuyenBay()
{
    strcpy(MaCB, "");
    NoiDen = "";
    this->next = NULL;
}

ChuyenBay::ChuyenBay(const char *_MaCB, string _NoiDen,
                     Date *_NgayGio, MayBay *_MayBay)
{
    this->MayBaySuDung = _MayBay;
    this->NgayGio = _NgayGio;
    strcpy(this->MaCB, _MaCB);
    this->NoiDen = _NoiDen;
    this->SoVeToiDa =
        this->MayBaySuDung->getSoDay() * MayBaySuDung->getSoDong();
}

char *ChuyenBay::getMaCB()
{
    return this->MaCB;
}

string ChuyenBay::getNoiDen()
{
    return this->NoiDen;
}

Date *ChuyenBay::getNgayGio()
{
    return this->NgayGio;
}

void ChuyenBay::setTrangThai(int _TrangThai)
{
    this->TrangThai = _TrangThai;
}

int ChuyenBay::getTrangThai()
{
    return this->TrangThai;
}

MayBay *ChuyenBay::getMayBay()
{
    return this->MayBaySuDung;
}

void ChuyenBay::setDSVeMB()
{
    if (MayBaySuDung == NULL)
        return;

    for (int i = 0; i < this->MayBaySuDung->getSoDay(); i++)
    {
        for (int j = 0; j < this->MayBaySuDung->getSoDong(); j++)
        {
            string tmp;
            tmp[0] = IDChu[i];
            tmp[1] = IDSo[this->MayBaySuDung->getSoDong() % 10];
            tmp[2] = IDSo[this->MayBaySuDung->getSoDong() -
                          ((this->MayBaySuDung->getSoDong() % 10) * 10)];
            tmp[3] = '\0';
            DSVe[i * this->MayBaySuDung->getSoDong() + j]->setIDVe(tmp);
        }
    }
}

void ChuyenBay::setNgayGio(Date *_NgayGio)
{
    this->NgayGio = _NgayGio;
}

/**
 * @note hàm chỉ làm mẫu, lúc xuất chỉnh trên UI sau
 */
void ChuyenBay::showDSVe()
{
    for (int i = 0; i < SoVeDaDat; i++)
    {
        HanhKhach *tmp;
        tmp = DSVe[i]->getHanhKhach();
        cout << i << ". " << DSVe[i]->getIDVe()
             << ", CMND: " << tmp->getCmnd()
             << "Ho va Ten: " << tmp->getHo() << " " << tmp->getTen()
             << endl;
    }
}

bool ChuyenBay::hasNext()
{
    if (this->next == NULL)
        return true;
    return false;
}

void ChuyenBay::setNext(ChuyenBay *node)
{
    node->next = this->next;
    this->next = node;
}

ChuyenBay *ChuyenBay::getNext()
{
    return this->next;
}
// Hàm của DanhSachCB

DanhSachCB::DanhSachCB()
{
    this->head = NULL;
}

DanhSachCB::DanhSachCB(ChuyenBay *cb)
{
    this->head = cb;
}

// ChuyenBay *DanhSachCB::getCBay()
// {
//     return this->cBay;
// }

void DanhSachCB::push(ChuyenBay *currNode, ChuyenBay *node)
{
    node->setNext(currNode->getNext());
    currNode->setNext(node);
}

void DanhSachCB::push_back(ChuyenBay *node)
{
    node->setNext(NULL);
    ChuyenBay *tmp = this->head;
    while (tmp->hasNext())
    {
        tmp = tmp->getNext();
    }
    tmp->setNext(node);
}

void DanhSachCB::push_front(ChuyenBay *node)
{
    node->setNext(this->head);
    this->head = node;
}

void DanhSachCB::pop(ChuyenBay *node)
{
    if (node == this->head)
    {
        this->pop_first();
        return;
    }
    else if (!node->hasNext())
    {
        this->pop_back();
        return;
    }

    ChuyenBay *tmp = this->head;
    while (tmp->getNext() != node)
    {
        tmp = tmp->getNext();
    }
    tmp->setNext(node->getNext());
}

void DanhSachCB::pop_first()
{
    this->head = this->head->getNext();
    ChuyenBay *tmp = this->head;
}

void DanhSachCB::pop_back()
{
    ChuyenBay *tmp = this->head;
    while (tmp->getNext()->hasNext())
    {
        tmp = tmp->getNext();
    }
    tmp->setNext(NULL);
}

ChuyenBay *DanhSachCB::TimCB(string _MaCB)
{
    ChuyenBay *tmp = this->head;
    while (tmp->hasNext())
    {
        if (tmp->getMaCB() == _MaCB)
        {
            return tmp;
        }
    }

    return NULL;
}
