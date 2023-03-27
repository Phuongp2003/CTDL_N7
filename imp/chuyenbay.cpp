#include "../header/chuyenbay.h"
using namespace std;

// hàm của ChuyenBay

ChuyenBay::ChuyenBay()
{
    strcpy(MaCB, "");
    NoiDen = "";
}

ChuyenBay::ChuyenBay(const char *_MaCB, string _NoiDen,
                     Date _NgayGio, char *_MaMayBay)
{
    strcpy(this->IDMayBay, _MaMayBay);
    this->NgayGio = _NgayGio;
    strcpy(this->MaCB, _MaCB);
    this->NoiDen = _NoiDen;
    this->TrangThai = ConVe;
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

char *ChuyenBay::getMaMayBay()
{
    return this->IDMayBay;
}

void ChuyenBay::setNgayGio(Date _NgayGio)
{
    this->NgayGio = _NgayGio;
}

DSVeMayBay *ChuyenBay::getDSVe()
{
    return this->DSVe;
}

/**
 * @brief Đây là hàm thử nghiệm
 *
 */
void ChuyenBay::ThucHienCB(DSMB *DanhSachMB)
{
    this->TrangThai = HoanTat;
    MayBay *tmp;
    tmp = DanhSachMB->getMB(DanhSachMB->Find_MB(this->MaCB));
    tmp->TangSLTHCB();
}

ChuyenBay *NodeCB::getNode()
{
    return this->node;
}

bool NodeCB::hasNext()
{
    if (this->next != NULL)
        return true;
    return false;
}

void NodeCB::setNext(NodeCB *node)
{
    node->next = this->next;
    this->next = node;
}

NodeCB *NodeCB::getNext()
{
    return this->next;
}
// Hàm của DanhSachCB

DanhSachCB::DanhSachCB()
{
    this->head = NULL;
}

DanhSachCB::DanhSachCB(NodeCB *node)
{
    this->head = node;
}

void DanhSachCB::push(NodeCB *currNode, NodeCB *node)
{
    currNode->setNext(node);
}

void DanhSachCB::push_back(NodeCB *node)
{
    node->setNext(NULL);
    NodeCB *tmp = this->head;
    while (tmp->hasNext())
    {
        tmp = tmp->getNext();
    }
    tmp->setNext(node);
}

void DanhSachCB::push_front(NodeCB *node)
{
    this->head->setNext(node);
    this->head = node;
}

void DanhSachCB::pop(NodeCB *node)
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

    NodeCB *tmp = this->head;
    while (tmp->getNext() != node)
    {
        tmp = tmp->getNext();
    }
    tmp->setNext(node->getNext());
}

void DanhSachCB::pop_first()
{
    this->head = this->head->getNext();
}

void DanhSachCB::pop_back()
{
    NodeCB *tmp = this->head;
    while (tmp->getNext()->hasNext())
    {
        tmp = tmp->getNext();
    }
    tmp->setNext(NULL);
}

ChuyenBay *DanhSachCB::TimCB(string _MaCB)
{
    NodeCB *tmp = this->head;
    while (tmp->hasNext())
    {
        if (tmp->getNode()->getMaCB() == _MaCB)
        {
            return tmp->getNode();
        }
    }

    return NULL;
}
