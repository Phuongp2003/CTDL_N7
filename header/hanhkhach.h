#pragma once
#include "chuyenbay.h"
#include "header.h"
// #include "vemaybay.h"

#include <fstream>

class HanhKhach
{
private:
  string cmnd;
  string ho;
  string ten;
  int phai; //  0 la nam, 1 la nu

public:
  HanhKhach();
  HanhKhach(string cmnd, string ho, string ten, int phai);

  string getCmnd();
  string getHo();
  string getTen();
  string getPhai();

  void setCmnd(string cmnd);
  void setHo(string ho);
  void setTen(string ten);
  void setPhai(int phai);
};

class NodeHK
{
private:
  HanhKhach hanhKhach;
  NodeHK *left;
  NodeHK *right;

public:
  NodeHK();
  NodeHK(HanhKhach hanhKhach);

  HanhKhach getHK();
  NodeHK *getLeft();
  NodeHK *getRight();

  void setLeft(NodeHK *left);
  void setRight(NodeHK *right);
};

class DsHanhKhach
{
private:
  NodeHK *root;
  int size = 0;

public:
  DsHanhKhach();
  bool insert(HanhKhach hanhKhach);
  NodeHK *search(string cmnd);
  void inOrderTraversal(NodeHK *node);
  void printInOrder();
  void showDsHanhKhach(string);
  void writeToFile(NodeHK *node);
  void readFromFile();
  NodeHK *getRoot();
  int getSize();
};

// function
int max(int a, int b);
