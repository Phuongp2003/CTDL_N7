#include "../header/hanhkhach.h"
#include <sstream>

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
    if (_phai == 0)
    {
        return "Nam";
    }
    else
        return "Nu";
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

NodeHK::NodeHK() {}

NodeHK::NodeHK(HanhKhach hanhKhach)
    : _hanhKhach(hanhKhach), _height(1), left(NULL), right(NULL) {}

HanhKhach NodeHK::getHanhKhach() const
{
    return _hanhKhach;
}

int NodeHK::getHeight() const
{
    return _height;
}

NodeHK *NodeHK::getLeft() const
{
    return left;
}

NodeHK *NodeHK::getRight() const
{
    return right;
}

void NodeHK::setHeight(int height)
{
    _height = height;
}

void NodeHK::setLeft(NodeHK *pLeft)
{
    left = pLeft;
}

void NodeHK::setRight(NodeHK *pRight)
{
    right = pRight;
}

//------------------------------------------------------------

DsHanhKhach::DsHanhKhach() : root(NULL) {}

bool DsHanhKhach::insert(HanhKhach hanhKhach)
{
    if (root == NULL)
    {
        root = new NodeHK(hanhKhach);
        writeToFile(root);
        return true;
    }

    NodeHK *current = root;
    while (true)
    {
        if (stoi(hanhKhach.getCmnd()) < stoi(current->getHanhKhach().getCmnd()))
        {
            if (current->getLeft() == NULL)
            {
                current->setLeft(new NodeHK(hanhKhach));
                writeToFile(current->getLeft());
                break;
            }
            else
            {
                current = current->getLeft();
            }
        }
        else if (stoi(hanhKhach.getCmnd()) > stoi(current->getHanhKhach().getCmnd()))
        {
            if (current->getRight() == NULL)
            {
                current->setRight(new NodeHK(hanhKhach));
                writeToFile(current->getRight());
                break;
            }
            else
            {
                current = current->getRight();
            }
        }
        else
        {
            current = NULL;
            break;
        }
    }
    return (current == NULL) ? false : true;
}

NodeHK *DsHanhKhach::search(string cmnd)
{
    if (root == NULL)
    {
        return NULL;
    }

    NodeHK *current = root;
    HanhKhach hanhKhach = current->getHanhKhach();

    while (current != NULL)
    {
        if (stoi(cmnd) == stoi(current->getHanhKhach().getCmnd()))
        {
            return current;
        }
        else if (stoi(cmnd) < stoi(current->getHanhKhach().getCmnd()))
        {
            current = current->getLeft();
        }
        else
        {
            current = current->getRight();
        }
    }

    return NULL;
}

void DsHanhKhach::inOrderTraversal(NodeHK *node)
{
    if (node == NULL)
    {
        return;
    }
    HanhKhach hanhKhach = node->getHanhKhach();
    inOrderTraversal(node->getLeft());
    cout << hanhKhach.getCmnd() << " | " << hanhKhach.getHo() << " " << hanhKhach.getTen() << " | " << hanhKhach.getPhai() << "\n";
    inOrderTraversal(node->getRight());
}

void DsHanhKhach::printInOrder()
{
    inOrderTraversal(root);
}

void DsHanhKhach::showDsHanhKhach(string maCb)
{
    DanhSachCB chuyenBay;
    ChuyenBay *cbCanTim = chuyenBay.TimCB(maCb);

    if (cbCanTim == NULL)
    {
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

    VeMayBay *dsVe = cbCanTim->getDSVe()->getDSVeMB();
    for (int i = 0; i < cbCanTim->getDSVe()->getSoVeToiDa(); i++)
    {
        if (!dsVe[i].getTrangThai())
        {
            NodeHK *tmp;
            tmp = this->search(dsVe[i].getHanhKhach());

            cout << i + 1 << '\t'
                 << dsVe[i].getIDVe() << '\t'
                 << tmp->getHanhKhach().getCmnd() << '\t'
                 << tmp->getHanhKhach().getHo() << ' '
                 << tmp->getHanhKhach().getTen() << '\t'
                 << tmp->getHanhKhach().getPhai() << '\t';
        }
    }
}

void DsHanhKhach::writeToFile(NodeHK *node)
{
    ofstream file;
    file.open("../dataHK.txt", ios::out | ios::app);
    if (file.is_open())
    {
        HanhKhach hanhKhach = node->getHanhKhach();
        string phai = (hanhKhach.getPhai() == "Nam") ? "0" : "1";
        file << hanhKhach.getCmnd() << '|' << hanhKhach.getHo() << '|' << hanhKhach.getTen() << '|' << phai << '\n';
        file.close();
    }
    else
        cout << "Error";
}

void DsHanhKhach::readFromFile()
{
    ifstream file;
    file.open("../test.txt");
    if (file.is_open())
    {
        string line;
        string cmnd, ho, ten, phai_str;
        int phai;
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, cmnd, '|');
            getline(ss, ho, '|');
            getline(ss, ten, '|');
            getline(ss, phai_str, '|');
            phai = phai_str == "Nam" ? 0 : 1;
            insert(HanhKhach(cmnd, ho, ten, phai));
        }
        file.close();
    }
    else
    {
        cout << "Error";
    }
}