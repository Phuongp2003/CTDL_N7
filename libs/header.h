#pragma once
// #include "mylib.h"
#include <iostream>
#include <string>

using namespace std;

// Hằng số ----------------------------------------------------------------

#define MAXMB 300
#define MAXVe 100

// struct -----------------------------------------------------------------

// ngày tháng
struct Date;
// Hành khách
struct Hanh_Khach;
struct Node; // @brief Node hành khách
// Máy bay
struct MayBay;
struct listMB;
// Chuyến bay
class VeMayBay;

// function ---------------------------------------------------------------

Node *create(Hanh_Khach hk);
Node *insert(Node *root, Hanh_Khach hk);
void inOrderTraversal(Node *root);
Node *searchByCMND(Node *root, string cmnd);