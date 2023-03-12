#pragma once
#include "header.h"

#ifndef HANHKHACH
#define HANHKHACH

class HanhKhach
{
private:
    string _cmnd;
    string _ho;
    string _ten;
    int _phai; //  0 la nam, 1 la nu

public:
    HanhKhach();
    HanhKhach(string, string, string, int);

    string getCmnd() const;
    string getHo() const;
    string getTen() const;
    string getPhai() const;

    void setCmnd(string);
    void setHo(string);
    void setTen(string);
    void setPhai(int);
};

class NodeHK
{
private:
    HanhKhach _hanhKhach;
    NodeHK *left;
    NodeHK *right;

public:
    NodeHK();
    NodeHK(HanhKhach);

    HanhKhach getHanhKhach() const;
    NodeHK *getLeft() const;
    NodeHK *getRight() const;

    void setLeft(NodeHK *);
    void setRight(NodeHK *);
};

class DsHanhKhach
{
private:
    NodeHK *root;

public:
    DsHanhKhach();
    void insert(HanhKhach);
    NodeHK *search(string);
    void showDsHanhKhach(string);
};

#endif