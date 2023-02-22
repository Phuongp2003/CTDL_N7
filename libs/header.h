#pragma once
// #include "mylib.h"
#include <iostream>
#include <string>

// using namespace std;

// Hằng số ----------------------------------------------------------------
#define string std::string
#define MAXMB 300
#define MAXVe 100

// struct -----------------------------------------------------------------

// Hành khách
struct HanhKhach;
struct Node; // @brief Node hành khách
// Máy bay
class MAYBAY;
struct listMB;
// Chuyến bay
class VeMayBay;

// function ---------------------------------------------------------------

Node *create(HanhKhach hk);
Node *insert(Node *root, HanhKhach hk);
void inOrderTraversal(Node *root);
Node *searchByCMND(Node *root, string cmnd);