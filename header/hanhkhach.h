#pragma once
#include "chuyenbay.h"
#include "header.h"
#include "vemaybay.h"

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
    int _height;
    NodeHK *left;
    NodeHK *right;

public:
    NodeHK();
    NodeHK(HanhKhach);

    HanhKhach getHanhKhach() const;
    int getHeight() const;
    NodeHK *getLeft() const;
    NodeHK *getRight() const;

    void setHeight(int);
    void setLeft(NodeHK *);
    void setRight(NodeHK *);
};

class DsHanhKhach
{
private:
    NodeHK *root;

public:
    DsHanhKhach();
    int getHeightTree(NodeHK *);
    int getBalaceFactor(NodeHK *);
    void updateHeight(NodeHK *);
    NodeHK *rotateLeft(NodeHK *);
    NodeHK *rotateRight(NodeHK *);
    void balance(NodeHK *);
    void insert(HanhKhach);
    NodeHK *search(string);
    void showDsHanhKhach(string);
};

// function
int max(int a, int b);