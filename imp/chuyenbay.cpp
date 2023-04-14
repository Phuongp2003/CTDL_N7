#include "../header/chuyenbay.h"
using namespace std;

// hàm của ChuyenBay

ChuyenBay::ChuyenBay()
{
    strcpy(MaCB, "");
    NgayGio = Date(1, 1, 1991, 0, 0);
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

bool ChuyenBay::checkNoiDen(const char *noiden)
{
    if (isGotStr(NoiDen, noiden))
        return true;
    return false;
}

bool ChuyenBay::checkTime(int ngay, int thang, int nam, int gio, int phut)
{
    if (NgayGio == Date(ngay, thang, nam, gio, phut))
        return true;
    return false;
}

bool ChuyenBay::checkMaCB(const char *maCB)
{
    if (isGotStr(MaCB, maCB))
        return true;
    return false;
}

void ChuyenBay::setDSVe(DSVeMayBay dsve)
{
    DSVe = dsve;
}

DSVeMayBay ChuyenBay::getDSVe()
{
    return this->DSVe;
}

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

Date ChuyenBay::NgayHoanThanh()
{
    Date date;
    if(NgayGio.getGio()+2<24)
    {
        date.setNgay(NgayGio.getNgay());
        date.setThang(NgayGio.getThang());
        date.setNam(NgayGio.getNam());
        date.setGio(NgayGio.getGio()+2);
        date.setPhut(NgayGio.getPhut());
    }
    else
    {
        date.setNgay(NgayGio.getNgay()+1);
        date.setThang(NgayGio.getThang());
        date.setNam(NgayGio.getNam());
        date.setGio(NgayGio.getGio()+2-24);
        date.setPhut(NgayGio.getPhut());
        
    }
    int thang;
    thang=NgayGio.getThang();
    if(thang==1 || thang==3 || thang==5 || thang==7 || thang==8 || thang==10  && date.getNgay()==32 )
    {
        date.setThang(thang+1);
        date.setNgay(1);
    }
    if(thang==12 && date.getNgay()==32 )
    {
        date.setThang(1);
        date.setNgay(1);
        date.setNam(NgayGio.getNam()+1);
    }
    if(thang==4 || thang==6 || thang==9 || thang==11  && date.getNgay()==31 )
    {
        date.setThang(thang+1);
        date.setNgay(1);
    }
    if(laNamNhuan(NgayGio.getNam())==1)
    {
        if(thang==2 && date.getNgay()==30)
        {
            date.setThang(3);
            date.setNgay(1);
        }
    }
    else
    {
        if(thang==2 && date.getNgay()==29)
        {
            date.setThang(3);
            date.setNgay(1);
        }   
    }


    
}

bool ChuyenBay::operator<(const ChuyenBay &other)
{
    int compare = strcmp(MaCB, other.MaCB);
    return (compare < 0) ? true : false;
}

ChuyenBay NodeCB::getNode()
{
    return this->node;
}

NodeCB::NodeCB()
{
    this->node = ChuyenBay();
    this->next = NULL;
}

void NodeCB::setNode(ChuyenBay node)
{
    this->node = node;
}

bool NodeCB::hasNext()
{
    if (this->next == NULL)
        return false;
    return true;
}

void NodeCB::setNext(NodeCB *node)
{
    this->next = node;
}

NodeCB *NodeCB::getNext()
{
    return this->next;
}

NodeCB *NodeCB::getTail()
{
    NodeCB *tmp = this;
    while (tmp->hasNext())
        tmp = tmp->getNext();
    return tmp;
}
// Hàm của DanhSachCB

DanhSachCB::DanhSachCB()
{
    this->head = NULL;
    size = 0;
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
    NodeCB *tmp = this->head;
    while (tmp->hasNext())
    {
        tmp = tmp->getNext();
    }
    tmp->setNext(node);
}

void DanhSachCB::push_front(NodeCB *node)
{
    if (this->head == NULL)
    {
        setHead(node);
    }
    else
    {
        NodeCB *tmp = this->head;
        while (tmp->hasNext())
        {
            NodeCB *tmp2 = tmp->getNext();
            if (tmp2 == node)
            {
                tmp2->setNext(NULL);
                break;
            }
        }
        node->getTail()->setNext(this->head);
        this->head = node;
    }
}
void DanhSachCB::setHead(NodeCB *head)
{
    this->head = head;
}

NodeCB *DanhSachCB::getHead()
{
    return head;
}

void DanhSachCB::setSize()
{
    NodeCB *tmp = this->head;
    while (tmp != NULL)
    {
        size++;
        tmp = tmp->getNext();
    }
}

int DanhSachCB::getSize()
{

    return size;
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
    if (this->head != NULL)
    {
        this->head = this->head->getNext();
        size--;
    }
}

void DanhSachCB::pop_back()
{
    if (this->head == NULL)
        return;
    NodeCB *tmp = this->head;
    while (tmp->getNext()->hasNext())
    {
        tmp = tmp->getNext();
    }
    tmp->setNext(NULL);
    size--;
}

ChuyenBay DanhSachCB::TimCB(string _MaCB)
{
    NodeCB *tmp = this->head;
    while (tmp != NULL)
    {
        if (tmp->getNode().getMaCB() == _MaCB)
        {
            return tmp->getNode();
        }
        tmp = tmp->getNext();
    }

    return ChuyenBay();
}

bool DanhSachCB::MayBayDangSuDung(const char* SoHieuMB)
{
    NodeCB *tmp = this->head;
    while (tmp != NULL)
    {
        if(tmp->getNode().getTrangThai()==1 || tmp->getNode().getTrangThai()==2)
        {
            if (tmp->getNode().getMaCB() == SoHieuMB)
                return true;
        }
        
        tmp = tmp->getNext();
    }

    return false;
}
bool DanhSachCB::DuocDatKhong(string CMND, ChuyenBay cb)
{
    NodeCB *tmp = this->head;
    for(int i=0;i<cb.getDSVe().getSoVeDaDat();i++)
    {
        if(cb.getDSVe().getVe(i).getHanhKhach() == CMND)
            return false;
    }
    while (tmp != NULL)
    {
        if(tmp->getNode().getTrangThai()==1 && tmp->getNode().getTrangThai()==2
           &&tmp->getNode().getNgayGio().getNgay()==cb.getNgayGio().getNgay()
           && tmp->getNode().getNgayGio().getThang()==cb.getNgayGio().getThang()
           && tmp->getNode().getNgayGio().getNam()==cb.getNgayGio().getNam()
           &&(
            tmp->getNode().getNgayGio().getGio()*60+tmp->getNode().getNgayGio().getPhut()<=cb.getNgayGio().getGio()*60+tmp->getNode().getNgayGio().getPhut()- 6*60
            ||tmp->getNode().getNgayGio().getGio()*60+tmp->getNode().getNgayGio().getPhut()>=cb.getNgayGio().getGio()*60+tmp->getNode().getNgayGio().getPhut()+ 6*60
            )
          )
        {
            for(int i=0;i<tmp->getNode().getDSVe().getSoVeDaDat();i++)
            {
                if(tmp->getNode().getDSVe().getVe(i).getHanhKhach() == CMND)
                    return false;
            }
        }
        
        tmp = tmp->getNext();
    }

    return true;
}




void DanhSachCB::ReadFromFile(ifstream &file)
{
    if (file.is_open())
    {
        string macb, noiden, trangthai, idmaybay, ngay, thang, nam, gio, phut;
        string line = "";

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
            Date d = Date(stoi(ngay), stoi(thang), stoi(nam), stoi(gio), stoi(phut));
            ChuyenBay cb = ChuyenBay(macb.c_str(), noiden, d, idmaybay.c_str());
            NodeCB *node = new NodeCB();
            node->setNode(cb);
            if (head == NULL)
            {
                setHead(node);
            }
            else
                push_back(node);
        }
        setSize();
        file.close();
    }
    else
        cout << "Error" << endl;
}
void DanhSachCB::WritetOfFile(ofstream &file)
{
    if (file.is_open())
    {
        NodeCB *tmp = this->head;
        while (tmp != NULL) //
        {
            file << tmp->getNode().getMaCB() << "|"
                 << tmp->getNode().getMaMayBay() << "|"
                 << tmp->getNode().getNgayGio().getNgay() << "|"
                 << tmp->getNode().getNgayGio().getThang() << "|"
                 << tmp->getNode().getNgayGio().getNam() << "|"
                 << tmp->getNode().getNgayGio().getGio() << "|"
                 << tmp->getNode().getNgayGio().getPhut() << "|"
                 << tmp->getNode().getNoiDen() << "|";

            tmp = tmp->getNext();
        }
    }
    else
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
