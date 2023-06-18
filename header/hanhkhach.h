#pragma once
#include "chuyenbay.h"
#include "header.h"

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

	void setHK(HanhKhach HanhKhach);
	void setLeft(NodeHK *left);
	void setRight(NodeHK *right);
};

class DsHanhKhach
{
private:
	NodeHK *root;
	int size;

	NodeHK *minLeftNode(NodeHK *node);
	NodeHK *search(NodeHK *&prevNode, string cmnd);
	void deleteDs(NodeHK *node);

public:
	DsHanhKhach();
	void insert(HanhKhach hanhKhach);
	NodeHK *search(string cmnd);
	void writeToFileOneHK(NodeHK *node);
	void writeToFileAllHK();
	void readFromFile();
	NodeHK *getRoot();
	int getSize();
	void remove(NodeHK *node);
	void deleteDs();
};
