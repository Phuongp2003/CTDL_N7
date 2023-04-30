#include "../header/hanhkhach.h"
#include <sstream>

HanhKhach::HanhKhach() : cmnd(""), ho(""), ten(""), phai(-1) {}

HanhKhach::HanhKhach(string cmnd, string ho, string ten, int phai)
{
  this->cmnd = cmnd;
  this->ho = ho;
  this->ten = ten;
  this->phai = phai;
}

string HanhKhach::getCmnd() { return this->cmnd; }

string HanhKhach::getHo() { return this->ho; }

string HanhKhach::getTen() { return this->ten; }

string HanhKhach::getPhai()
{
  if (phai == 0)
  {
    return "Nam";
  }
  else
    return "Nu";
}

void HanhKhach::setCmnd(string cmnd) { this->cmnd = cmnd; }

void HanhKhach::setHo(string ho) { this->ho = ho; }

void HanhKhach::setTen(string ten) { this->ten = ten; }

void HanhKhach::setPhai(int phai) { this->phai = phai; }

//------------------------------------------------------------

NodeHK::NodeHK() {}

NodeHK::NodeHK(HanhKhach hanhKhach)
{
  this->hanhKhach = hanhKhach;
  this->left = NULL;
  this->right = NULL;
}

HanhKhach NodeHK::getHK() { return this->hanhKhach; }

NodeHK *NodeHK::getLeft() { return this->left; }

NodeHK *NodeHK::getRight() { return this->right; }

void NodeHK::setLeft(NodeHK *left) { this->left = left; }

void NodeHK::setRight(NodeHK *right) { this->right = right; }

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
    if (stoi(hanhKhach.getCmnd()) < stoi(current->getHK().getCmnd()))
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
    else if (stoi(hanhKhach.getCmnd()) >
             stoi(current->getHK().getCmnd()))
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
  HanhKhach hanhKhach = current->getHK();

  while (current != NULL)
  {
    if (stoi(cmnd) == stoi(current->getHK().getCmnd()))
    {
      return current;
    }
    else if (stoi(cmnd) < stoi(current->getHK().getCmnd()))
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
  HanhKhach hanhKhach = node->getHK();
  inOrderTraversal(node->getLeft());
  cout << hanhKhach.getCmnd() << " | " << hanhKhach.getHo() << " "
       << hanhKhach.getTen() << " | " << hanhKhach.getPhai() << "\n";
  inOrderTraversal(node->getRight());
}

void DsHanhKhach::printInOrder() { inOrderTraversal(root); }

// void DsHanhKhach::showDsHanhKhach(string maCb)
// {
//     DsChuyenBay chuyenBay;
//     ChuyenBay cbCanTim = chuyenBay.TimCB(maCb);

//     if (cbCanTim == NULL)
//     {
//         cout << "Khong ton tai chuyen bay";
//         return;
//     }

//     cout << "DANH SACH HANH KHACH THUOC CHUYEN BAY " << cbCanTim->getMaCB();

//     Date ngayGio = cbCanTim->getNgayGio();
//     cout << "\nNgay gio khoi hanh: "
//          << ngayGio.getThang() << "/"
//          << ngayGio.getNgay() << "/"
//          << ngayGio.getNam() << " "
//          << ngayGio.getGio() << ":"
//          << ngayGio.getPhut() << ". "
//          << "Noi den: " << cbCanTim->getNoiDen() << "\n\n";

//     cout << "STT\tSO VE\tSO CMND\t\tHO TEN\t\t\tPHAI";

//     VeMayBay *dsVe = cbCanTim->getDSVe()->getDSVeMB();
//     for (int i = 0; i < cbCanTim->getDSVe()->getSoVeToiDa(); i++)
//     {
//         if (!dsVe[i].getTrangThai())
//         {
//             NodeHK *tmp;
//             tmp = this->search(dsVe[i].getHanhKhach());

//             cout << i + 1 << '\t'
//                  << dsVe[i].getIDVe() << '\t'
//                  << tmp->getHanhKhach().getCmnd() << '\t'
//                  << tmp->getHanhKhach().getHo() << ' '
//                  << tmp->getHanhKhach().getTen() << '\t'
//                  << tmp->getHanhKhach().getPhai() << '\t';
//         }
//     }
// }

void DsHanhKhach::writeToFile(NodeHK *node)
{
  ofstream file;
  file.open("../data/dataHK.txt", ios::out | ios::app);
  if (file.is_open())
  {
    HanhKhach hanhKhach = node->getHK();
    string phai = (hanhKhach.getPhai() == "Nam") ? "0" : "1";
    file << hanhKhach.getCmnd() << '|' << hanhKhach.getHo() << '|'
         << hanhKhach.getTen() << '|' << phai << '\n';
    file.close();
  }
  else
    cout << "Error";
}

void DsHanhKhach::readFromFile()
{
  ifstream file;
  file.open("../data/dataHK.txt", ios::in);
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
      phai = phai_str == "0" ? 0 : 1;
      insert(HanhKhach(cmnd, ho, ten, phai));
    }
    file.close();
  }
  else
  {
    cout << "Error";
  }
}

int DsHanhKhach::getSize() { return this->size; }

NodeHK *DsHanhKhach::getRoot() { return this->root; }