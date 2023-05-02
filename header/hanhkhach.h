#pragma once
#include "chuyenbay.h"
#include "header.h"
#include "queue.h"
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

  void writeToFileHelper(ofstream &file, NodeHK *node);
  void levelOrderTraversalHelper(NodeHK *node, int level, Queue &queue);
  int getHeight(NodeHK *node);

public:
  DsHanhKhach();
  bool insert(HanhKhach hanhKhach);
  NodeHK *search(string cmnd);
  void inOrderTraversal(NodeHK *node);
  void printInOrder();
  Queue getDsHanhKhach(string maCB, DsChuyenBay dsChuyenBay);
  void writeToFileOneHK(NodeHK *node);
  void writeToFileAllHK();
  void readFromFile();
  NodeHK *getRoot();
  int getSize();
  void levelOrderTraversal(Queue &queue);
};

// function
int max(int a, int b);
