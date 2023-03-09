#include "hanhkhach.h"
#include "chuyenbay.h"

using namespace std;

HanhKhach::HanhKhach() : _cmnd(""), _ho(""), _ten(""), _phai(-1) {}

HanhKhach::HanhKhach(string cmnd, string ho, string ten, int phai)
    : _cmnd(cmnd), _ho(ho), _ten(ten), _phai(phai) {}

string HanhKhach::getCmnd() const
{
    return _cmnd;
}

string HanhKhach::getHo() const
{
    return _ho;
}

string HanhKhach::getTen() const
{
    return _ten;
}

string HanhKhach::getPhai() const
{
    if (_phai == 0) {
        return "Nam";
    } else return "Nu";
}

void HanhKhach::setCmnd(string cmnd)
{
    _cmnd = cmnd;
}

void HanhKhach::setHo(string ho)
{
    _ho = ho;
}

void HanhKhach::setTen(string ten)
{
    _ten = ten;
}

void HanhKhach::setPhai(int phai)
{
    _phai = phai;
}

//------------------------------------------------------------

DsHanhKhach::DsHanhKhach() : root(NULL) {}

void DsHanhKhach::insert(HanhKhach hanhKhach)
{
    Node *newNode = new Node;
    newNode->_hanhKhach = hanhKhach;
    newNode->left = newNode->right = NULL;

    if (root == NULL)
    {
        root = newNode;
        return;
    }

    Node *current = root;
    int compareCmnd;
    while (true)
    {
        compareCmnd = hanhKhach.getCmnd().compare(current->_hanhKhach.getCmnd());

        if (compareCmnd < 0)
        {
            if (current->left == NULL)
            {
                current->left = newNode;
                break;
            }
            else
            {
                current = current->left;
            }
        }
        else
        {
            if (current->right == NULL)
            {
                current->right = newNode;
                break;
            }
            else
            {
                current = current->right;
            }
        }
    }
}

DsHanhKhach::Node *DsHanhKhach::search(string cmnd)
{
    if (root == NULL)
    {
        return NULL;
    }

    int compareCmnd;

    while (root != NULL)
    {
        compareCmnd = cmnd.compare(root->_hanhKhach.getCmnd());
        if (compareCmnd == 0) {
            return root;
        } else if (compareCmnd < 0) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    return NULL;
}

void DsHanhKhach::showDsHanhKhach(string maCb)
{
    DanhSachCB chuyenBay;
    ChuyenBay *cbCanTim = chuyenBay.TimCB(maCb);

    if (cbCanTim == NULL) {
        cout << "Khong ton tai chuyen bay";
        return;
    }

    cout << "DANH SACH HANH KHACH THUOC CHUYEN BAY " << cbCanTim->getMaCB();

    Date ngayGio = cbCanTim->getNgayGio();
    cout << "\nNgay gio khoi hanh: "
         << ngayGio.getThang() << "/"
         << ngayGio.getNgay() << "/"
         << ngayGio.getNam() << " "
         << ngayGio.getGio() << ":"
         << ngayGio.getPhut() << ". "
         << "Noi den: " << cbCanTim->getNoiDen() << "\n\n";
         
    cout << "STT\tSO VE\tSO CMND\t\tHO TEN\t\t\tPHAI";
    
    VeMayBay *dsVe = cbCanTim->getDSVe();
    for (int i = 0; i < cbCanTim->getSoVeToiDa(); i++) {
        if (!dsVe[i].getTrangThai()) {
            cout << i + 1 << '\t'
                 << dsVe[i].getIDVe() << '\t'
                 << dsVe[i].getHanhKhach()->getCmnd() << '\t'
                 << dsVe[i].getHanhKhach()->getHo() << ' '
                 << dsVe[i].getHanhKhach()->getTen() << '\t'
                 << dsVe[i].getHanhKhach()->getPhai() << '\t';
        }
    }
}