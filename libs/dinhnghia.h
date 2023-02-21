#include "header.h"

// Hằng số ----------------------------------------------------------------

// struct -----------------------------------------------------------------
struct Hanh_Khach;
struct Node; // @brief Node hành khách

// function ---------------------------------------------------------------

Node *create(Hanh_Khach hk);
Node *insert(Node *root, Hanh_Khach hk);
void inOrderTraversal(Node *root);
Node *searchByCMND(Node *root, string cmnd);