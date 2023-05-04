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
        size++;
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
                size++;
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
                size++;
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

// Queue DsHanhKhach::getDsHanhKhach(string maCB, DsChuyenBay dsChuyenBay)
// {
//     NodeCB *nodeCB = dsChuyenBay.timCB(maCB);
//     Queue queue = Queue(this->size);

//     if (nodeCB == NULL)
//     {
//         return queue;
//     }
//     VeMayBay *dsVe = nodeCB->getNode().getDSVe().getDSVeMB();
//     string cmnd;
//     NodeHK *nodeHK;
//     for (int i = 0; i < dsChuyenBay.getSize(); i++)
//     {
//         cmnd = dsVe[i].getHanhKhach();
//         nodeHK = search(cmnd);
//         queue.push(nodeHK);
//     }
//     return queue;
// }

void DsHanhKhach::writeToFileOneHK(NodeHK *node)
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

void DsHanhKhach::writeToFileHelper(ofstream &file, NodeHK *node)
{
    if (node == NULL)
    {
        return;
    }
    HanhKhach hanhKhach = node->getHK();
    string phai = (hanhKhach.getPhai() == "Nam") ? "0" : "1";
    file << hanhKhach.getCmnd() << '|' << hanhKhach.getHo() << '|'
         << hanhKhach.getTen() << '|' << phai << '\n';
    writeToFileHelper(file, node->getLeft());
    writeToFileHelper(file, node->getRight());
}

void DsHanhKhach::writeToFileAllHK()
{
    ofstream file;
    file.open("../data/dataHK.txt", ios::trunc);

    if (file.is_open())
    {
        writeToFileHelper(file, root);
    }

    file.close();
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

int DsHanhKhach::getHeight(NodeHK *node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        int leftHeight = getHeight(node->getLeft());
        int rightHeight = getHeight(node->getRight());

        if (leftHeight > rightHeight)
        {
            return leftHeight + 1;
        }
        else
        {
            return rightHeight + 1;
        }
    }
}

// void DsHanhKhach::levelOrderTraversalHelper(NodeHK *node, int level, Queue &queue)
// {
//     if (node == NULL)
//     {
//         return;
//     }
//     if (level == 1)
//     {
//         queue.push(node);
//     }
//     else
//     {
//         levelOrderTraversalHelper(node->getLeft(), level - 1, queue);
//         levelOrderTraversalHelper(node->getRight(), level - 1, queue);
//     }
// }

// void DsHanhKhach::levelOrderTraversal(Queue &queue)
// {
//     int height = getHeight(root);

//     for (int i = 1; i <= height; i++)
//     {
//         levelOrderTraversalHelper(root, i, queue);
//     }
// }
