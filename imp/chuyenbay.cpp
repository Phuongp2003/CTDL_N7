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
// VeMayBay* ChuyenBay::GetDSVeTrong()
// {
//     VeMayBay *DSVeTrong=new VeMayBay[DSVe->getSoVeToiDa()];
//     for(int )
// }

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
NodeCB *DanhSachCB::getHead()
{
    return head;
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
DanhSachCB DanhSachCB::TimDSCB(Date date, string noiden)
{
    NodeCB *tmp = this->head;
    DanhSachCB *DS = new DanhSachCB();
    while (tmp != NULL)
    {
        if ((tmp->getNode()->getNgayGio().getNgay() == date.getNgay()) && (tmp->getNode()->getNgayGio().getThang() == date.getThang()) && (tmp->getNode()->getNgayGio().getNam() == date.getNam()) && (tmp->getNode()->getNoiDen() == noiden) && ((tmp->getNode()->getDSVe()->getSoVeConLai() != 0)))
        {
            if (DS->getHead() == NULL)
                DS->push_front(tmp);
            else
                DS->push_back(tmp);
        }
        tmp = tmp->getNext();
    }
    return *DS;
}

DanhSachCB DanhSachCB::LocDSCB(string _keyword)
{
    NodeCB *tmp = this->head;
    DanhSachCB *result = new DanhSachCB();
    while (tmp != NULL)
    {
        if (isGotStr(tmp->getNode()->getMaCB(), _keyword))
        {
            if (result->getHead() == NULL)
                result->push_front(tmp);
            else
                result->push_back(tmp);
        }
        tmp = tmp->getNext();
    }
    return *result;
}

bool isGotStr(string _string, string _keyword)
{
    if (_string.length() < _keyword.length())
        return false;
    bool status = false;
    for (int i = 0; i <= _string.length() - _keyword.length(); i++)
    {
        if (_string[i] == _keyword[0])
        {
            status = true;
            for (int j = i + 1; j < i + _keyword.length(); j++)
            {
                if (_string[j] != _keyword[j - i])
                {
                    status = false;
                    continue;
                }
            }
        }
        if (status == true)
            return true;
    }
    return false;
}