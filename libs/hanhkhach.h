#pragma once
#include "header.h"

class HanhKhach
{
private:
    string _cmnd;
    string _ho;
    string _ten;
    int _phai;
public:
    HanhKhach();
    HanhKhach(string, string, string, int);

    string getCmnd() const;
    string getHo() const;
    string getTen() const;
    int getPhai() const;

    void setCmnd(string);
    void setHo(string);
    void setTen(string);
    void setPhai(int);
};

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

int HanhKhach::getPhai() const
{
    return _phai;
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

class Node
{
public:
    HanhKhach _hanhKhach;
    Node *left;
    Node *right;
    Node(HanhKhach);
};

Node::Node(HanhKhach hanhKhach)
    : _hanhKhach(hanhKhach), left(NULL), right(NULL) {}

class BstHanhKhach
{
private:
    Node *root;
public:
    BstHanhKhach();
    Node *insert(Node *, HanhKhach);
    Node *search(Node *, string);
    void showDsHanhKhach(string);
};

BstHanhKhach::BstHanhKhach() : root(NULL) {}

Node *BstHanhKhach::insert(Node *root, HanhKhach hanhKhach)
{
    if (root == NULL)
    {
        return new Node(hanhKhach);
    }

    int compareCmnd = 
        hanhKhach.getCmnd().compare(root->_hanhKhach.getCmnd());
    
    if (compareCmnd < 0)
    {
        root->left = insert(root->left, hanhKhach);
    }
    else
    {
        root->right = insert(root->right, hanhKhach);
    }

    return root;
}

Node *BstHanhKhach::search(Node *root, string cmnd)
{
    if (root == NULL || root->_hanhKhach.getCmnd() == cmnd)
    {
        return root;
    }

    int compareCmnd = cmnd.compare(root->_hanhKhach.getCmnd());

    if (compareCmnd < 0)
    {
        return search(root->left, cmnd);
    }
    else
    {
        return search(root->right, cmnd);
    }
}

void BstHanhKhach::showDsHanhKhach(string maCb) {
    cout << "DANH SACH HANH KHACH THUOC CHUYEN BAY ";
}