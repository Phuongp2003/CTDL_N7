#include "../header/chuyenbay.h"
using namespace std;
// hàm của DSVe

VeMayBay::VeMayBay()
{
    IDVe = "A00";
    CMND = "\0";
    TrangThai = true;
}

VeMayBay::VeMayBay(string IDVe, string CMND)
{
    this->IDVe = IDVe;
    this->CMND = CMND;
}

void VeMayBay::setIDVe(string ID)
{
    this->IDVe = ID;
}

string VeMayBay::getIDVe()
{
    return this->IDVe;
}

void VeMayBay::setHanhKhach(string CMND)
{
    this->CMND = CMND;
}

string VeMayBay::getHanhKhach()
{
    return this->CMND;
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

int ChuyenBay::getSoVeToiDa()
{
    return this->SoVeToiDa;
}

char *ChuyenBay::getMaMayBay()
{
    return this->IDMayBay;
}

void ChuyenBay::setNgayGio(Date _NgayGio)
{
    this->NgayGio = _NgayGio;
}

void ChuyenBay::setDSVeMB(DSMB *DanhSachMB)
{
    MayBay *tmp;
    tmp = DanhSachMB->getMB(DanhSachMB->Find_MB(this->IDMayBay));
    int SDay, SDong;
    SDay = tmp->getSoDay();
    SDong = tmp->getSoDong();
    this->SoVeToiDa = SDay * SDong;
    DSVe = new VeMayBay[this->SoVeToiDa];
    for (int i = 0; i < SDay; i++)
    {
        for (int j = 0; j < SDong; j++)
        {
            string tmp_str;
            tmp_str += IDChu[i];
            tmp_str += IDSo[(j + 1) / 10];
            tmp_str += IDSo[(j + 1) % 10];
            tmp_str += '\0';
            // tmp_str = tmp_str;
            DSVe[i * SDong + j].setIDVe(tmp_str);
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
void ChuyenBay::showDSVe()
{
    for (int i = 0; i < SoVeToiDa; i++)
    {
        cout << i << ". " << this->DSVe[i].getIDVe() << " ";
        if (this->DSVe[i].getHanhKhach() == "\0")
            cout << "Con ve" << endl;
        else
            cout << "Da dat" << endl;
    }
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

ChuyenBay *Node_CB::getNode()
{
    return this->node;
}

bool Node_CB::hasNext()
{
    if (this->next != NULL)
        return true;
    return false;
}

void Node_CB::setNext(Node_CB *node)
{
    node->next = this->next;
    this->next = node;
}

Node_CB *Node_CB::getNext()
{
    return this->next;
}
// Hàm của DanhSachCB

DanhSachCB::DanhSachCB()
{
    this->head = NULL;
}

DanhSachCB::DanhSachCB(Node_CB *node)
{
    this->head = node;
}

void DanhSachCB::push(Node_CB *currNode, Node_CB *node)
{
    currNode->setNext(node);
}

void DanhSachCB::push_back(Node_CB *node)
{
    node->setNext(NULL);
    Node_CB *tmp = this->head;
    while (tmp->hasNext())
    {
        tmp = tmp->getNext();
    }
    tmp->setNext(node);
}

void DanhSachCB::push_front(Node_CB *node)
{
    this->head->setNext(node);
    this->head = node;
}

void DanhSachCB::pop(Node_CB *node)
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

    Node_CB *tmp = this->head;
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
    Node_CB *tmp = this->head;
    while (tmp->getNext()->hasNext())
    {
        tmp = tmp->getNext();
    }
    tmp->setNext(NULL);
}

ChuyenBay *DanhSachCB::TimCB(string _MaCB)
{
    Node_CB *tmp = this->head;
    while (tmp->hasNext())
    {
        if (tmp->getNode()->getMaCB() == _MaCB)
        {
            return tmp->getNode();
        }
    }

    return NULL;
}