#include "../header/chuyenbay.h"
using namespace std;

// hàm của ChuyenBay

ChuyenBay::ChuyenBay()
{
    strcpy(MaCB, "");
    NoiDen = "";
}

ChuyenBay::ChuyenBay(const char *_MaCB, string _NoiDen,
                     Date _NgayGio, const char *_MaMayBay)
{
    strcpy(this->MaCB, _MaCB);
    strcpy(this->IDMayBay, _MaMayBay);
    this->NgayGio = _NgayGio;
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

const char *ChuyenBay::getMaMayBay()
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
    //     this->TrangThai = HoanTat;
    //     MayBay *tmp;
    //     tmp = DanhSachMB->getMB(DanhSachMB->Find_MB(this->MaCB));
    //     tmp->TangSLTHCB();
}

bool ChuyenBay::operator<(const ChuyenBay &other)
{
    int compare = strcmp(MaCB, other.MaCB);
    return (compare < 0) ? true : false;
}

ChuyenBay *NodeCB::getNode()
{
    return this->node;
}

void NodeCB::setNode(ChuyenBay *node)
{
    this->node = node;
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
void DanhSachCB::setHead(NodeCB *head)
{
    this->head=head;
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
    while (tmp != NULL)
    {
        if (tmp->getNode()->getMaCB() == _MaCB)
        {
            return tmp->getNode();
        }
        tmp = tmp->getNext();
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
void  DanhSachCB::ReadFromFile(ifstream &file)
{
    if(file.is_open())
    {
        string macb,noiden,trangthai,idmaybay,ngay,thang,nam,gio,phut;
        string line="";
        NodeCB *node;
        ChuyenBay *cb;
        while (getline(file, line))
        {
            stringstream s(line);
            getline(s, macb, '|');
            getline(s, idmaybay, '|');
            getline(s, ngay, '|');
            getline(s, thang, '|');
            getline(s, nam, '|');
            getline(s, gio, '|');
            getline(s, phut, '|');
            getline(s, noiden, '|');            
            cb=new ChuyenBay(macb.c_str(),noiden,Date(stoi(gio),stoi(phut),stoi(ngay),stoi(thang),stoi(nam)),idmaybay.c_str());
            node->setNode(cb);
            if(head ==NULL)
            {
                push_back(node);
            }
            else push_front(node);
        }
        file.close();
    }
    else
        cout << "Error" << endl;
}
void  DanhSachCB::WritetOfFile(ofstream &file)
{
    if (file.is_open())
    {
        NodeCB *tmp = this->head;
        while (tmp != NULL)//
        {
            file<<tmp->getNode()->getMaCB()<<"|"
                <<tmp->getNode()->getMaMayBay()<<"|"
                <<tmp->getNode()->getNgayGio().getNgay()<<"|"
                <<tmp->getNode()->getNgayGio().getThang()<<"|"
                <<tmp->getNode()->getNgayGio().getNam()<<"|"
                <<tmp->getNode()->getNgayGio().getGio()<<"|"
                <<tmp->getNode()->getNgayGio().getPhut()<<"|"
                <<tmp->getNode()->getNoiDen()<<"|";

            tmp = tmp->getNext();
        }  
    }else
    {
        cout << "Error";
    }
    file.close();
}


NodeCB *DanhSachCB::merge(NodeCB *left, NodeCB *right)
{
    if (left == NULL)
    {
        return right;
    }
    if (right == NULL)
    {
        return left;
    }

    NodeCB *final;

    if (left->getNode() < right->getNode())
    {
        final = left;
        final->setNext(merge(left->getNext(), right));
    }
    else
    {
        final = right;
        final->setNext(merge(left, right->getNext()));
    }
    return final;
}

NodeCB *DanhSachCB::mid_point(NodeCB *node)
{
    if (node == NULL || !node->hasNext())
    {
        return node;
    }

    NodeCB *slow = head;
    NodeCB *fast = head;

    while (fast != NULL && fast->hasNext())
    {
        fast = fast->getNext();

        if (!fast->hasNext())
        {
            break;
        }

        fast = fast->getNext();
        slow = slow->getNext();
    }

    return slow;
}

NodeCB *DanhSachCB::sort(NodeCB *node)
{
    if (node == NULL || !node->hasNext())
    {
        return node;
    }

    NodeCB *mid = mid_point(node);
    NodeCB *left = node;
    NodeCB *right = mid->getNext();
    mid->setNext(NULL);

    left = sort(left);
    right = sort(right);

    NodeCB *final = merge(left, right);
    return final;
}