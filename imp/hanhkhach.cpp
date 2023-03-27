#include "../header/hanhkhach.h"

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

int DsHanhKhach::getHeightTree(NodeHK *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->getHeight();
}

int DsHanhKhach::getBalaceFactor(NodeHK *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return getHeightTree(node->getLeft()) - getHeightTree(node->getRight() + 1);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void DsHanhKhach::updateHeight(NodeHK *node)
{
    int maxHeight = max(getHeightTree(node->getLeft()), getHeightTree(node->getRight()));
    node->setHeight(maxHeight);
}

NodeHK *DsHanhKhach::rotateLeft(NodeHK *node)
{
    NodeHK *x = node->getRight();
    NodeHK *y = x->getLeft();

    x->setLeft(node);
    node->setRight(y);

    updateHeight(node);
    updateHeight(x);

    return x;
}

NodeHK *DsHanhKhach::rotateRight(NodeHK *node)
{
    NodeHK *x = node->getLeft();
    NodeHK *y = node->getRight();

    x->setRight(node);
    node->setLeft(y);

    updateHeight(node);
    updateHeight(x);

    return x;
}

void DsHanhKhach::balance(NodeHK *node)
{
    if (getBalaceFactor(node) > 1)
    {
        if (getBalaceFactor(node->getLeft()) < 0)
        {
            node->setLeft(rotateLeft(node->getLeft()));
        }
        node->setLeft(rotateRight(node));
    }
    else if (getBalaceFactor(node) < -1)
    {
        if (getBalaceFactor(node->getRight()) > 0)
        {
            node->setRight(rotateRight(node->getRight()));
        }
        node->setRight(rotateLeft(node));
    }
}

void DsHanhKhach::insert(HanhKhach hanhKhach)
{
    if (root == NULL)
    {
        root = new NodeHK(hanhKhach);
        return;
    }

    int compareCmnd;
    while (true)
    {
        compareCmnd = hanhKhach.getCmnd().compare(root->getHanhKhach().getCmnd());

        if (compareCmnd < 0)
        {
            if (root->getLeft() == NULL)
            {
                root->setLeft(new NodeHK(hanhKhach));
                break;
            }
            else
            {
                root = root->getLeft();
            }
        }
        else
        {
            if (root->getRight() == NULL)
            {
                root->setRight(new NodeHK(hanhKhach));
                break;
            }
            else
            {
                root = root->getRight();
            }
        }
    }

    updateHeight(root);
    balance(root);
}

NodeHK *DsHanhKhach::search(string cmnd)
{
    if (root == NULL)
    {
        return NULL;
    }

    int compareCmnd;

    while (root != NULL)
    {
        compareCmnd = cmnd.compare(root->getHanhKhach().getCmnd());
        if (compareCmnd == 0)
        {
            return root;
        }
        else if (compareCmnd < 0)
        {
            root = root->getLeft();
        }
        else
        {
            root = root->getRight();
        }
    }

    return NULL;
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