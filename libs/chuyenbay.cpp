#include "chuyenbay.h"
using namespace std;

// hàm của DSVe

VeMayBay::VeMayBay()
{
    IDVe = "A00";
    HanhKhachMuaVe = NULL;
    TrangThai = true;
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

bool VeMayBay::getTrangThai()
{
    return this->TrangThai;
}

// hàm của ChuyenBay

ChuyenBay::ChuyenBay()
{
    strcpy(MaCB, "");
    NoiDen = "";
    this->next = NULL;
}

ChuyenBay::ChuyenBay(const char *_MaCB, string _NoiDen,
                     Date _NgayGio, MayBay *_MayBay)
{
    this->MayBaySuDung = _MayBay;
    this->NgayGio = _NgayGio;
    strcpy(this->MaCB, _MaCB);
    this->NoiDen = _NoiDen;
    this->SoVeToiDa =
        this->MayBaySuDung->getSoDay() * MayBaySuDung->getSoDong();
    this->TrangThai = ConVe;
    DSVe = new VeMayBay[SoVeToiDa];
    for (int i = 0; i < this->SoVeToiDa; i++)
    {
        DSVe[i] = VeMayBay();
    }
}

char *ChuyenBay::getMaCB()
{
    return this->MaCB;
}

string ChuyenBay::getNoiDen()
{
    return this->NoiDen;
}

Date ChuyenBay::getNgayGio()
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

int ChuyenBay::getSoVeToiDa()
{
    return this->SoVeToiDa;
}

MayBay *ChuyenBay::getMayBay()
{
    return this->MayBaySuDung;
}

void ChuyenBay::setNgayGio(Date _NgayGio)
{
    this->NgayGio = _NgayGio;
}

void ChuyenBay::setDSVeMB()
{
    if (MayBaySuDung == NULL)
        return;

    for (int i = 0; i < this->MayBaySuDung->getSoDay(); i++)
    {
        for (int j = 0; j < this->MayBaySuDung->getSoDong(); j++)
        {
            string tmp_str;
            char tmp[4];
            tmp[0] = IDChu[i];
            tmp[1] = IDSo[(j + 1) / 10];
            tmp[2] = IDSo[(j + 1) % 10];
            tmp[3] = '\0';
            tmp_str = tmp;
            DSVe[i * this->MayBaySuDung->getSoDong() + j].setIDVe(tmp_str);
        }
    }
}
VeMayBay *ChuyenBay::getDSVe()
{
    return this->DSVe;
}

/**
 * @note hàm chỉ làm mẫu, lúc xuất chỉnh trên UI sau
 */
void ChuyenBay::showDSVeTrong()
{
    HanhKhach *hanhKhach;
    for (int i = 0; i < SoVeToiDa; i++)
    {
        hanhKhach = DSVe[i].getHanhKhach();
        if (this->DSVe[i].getTrangThai())
        {
            cout << i + 1
                 << DSVe[i].getIDVe()
                 << hanhKhach->getCmnd()
                 << hanhKhach->getHo()
                 << hanhKhach->getTen()
                 << hanhKhach->getPhai();
        }
    }
}
/**
 * @brief Đây là hàm thử nghiệm
 *
 */
void ChuyenBay::ThucHienCB()
{
    this->TrangThai = HoanTat;
    this->MayBaySuDung->TangSLTHCB();
}

bool DanhSachCB::hasNext(Node *currNode)
{
    if (currNode->next == NULL)
        return true;
    return false;
}

void DanhSachCB::setNext(Node *currNode, Node *node)
{
    node->next = currNode->next;
    currNode->next = node;
}

DanhSachCB::Node *DanhSachCB::getNext(Node *currNode)
{
    return currNode;
}
// Hàm của DanhSachCB

DanhSachCB::DanhSachCB()
{
    this->head = NULL;
}

DanhSachCB::DanhSachCB(Node *node)
{
    this->head = node;
}

void DanhSachCB::push(Node *currNode, Node *node)
{
    setNext(currNode, node);
}

void DanhSachCB::push_back(Node *node)
{
    setNext(node, NULL);
    Node *tmp = this->head;
    while (hasNext(tmp))
    {
        tmp = getNext(tmp);
    }
    setNext(tmp, node);
}

void DanhSachCB::push_front(Node *node)
{
    setNext(node, this->head);
    this->head = node;
}

void DanhSachCB::pop(Node *node)
{
    if (node == this->head)
    {
        this->pop_first();
        return;
    }
    else if (!hasNext(node))
    {
        this->pop_back();
        return;
    }

    Node *tmp = this->head;
    while (getNext(tmp) != node)
    {
        tmp = getNext(tmp);
    }
    setNext(tmp, getNext(node));
}

void DanhSachCB::pop_first()
{
    this->head = getNext(this->head);
}

void DanhSachCB::pop_back()
{
    Node *tmp = this->head;
    while (hasNext(getNext(tmp)))
    {
        tmp = getNext(tmp);
    }
    setNext(tmp, NULL);
}

ChuyenBay *DanhSachCB::TimCB(string _MaCB)
{
    Node *tmp = this->head;
    while (hasNext(tmp))
    {
        if (tmp->node->getMaCB() == _MaCB)
        {
            return tmp->node;
        }
    }

    return NULL;
}