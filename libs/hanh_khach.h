#include <iostream>
#include <string>

using namespace std;

struct Hanh_Khach
{
    char CMND[27];
    string ho;
    string ten;
    int phai;
};

struct Node
{
    Hanh_Khach data;
    Node *left;
    Node *right;
};

Node *create(Hanh_Khach hk)
{
    Node *newNode = new Node;
    newNode->data = hk;
    newNode->left = newNode->right = NULL;

    return newNode;
}

Node *insert(Node *root, Hanh_Khach hk)
{
    if (root == NULL)
    {
        return create(hk);
    }

    if (hk.CMND < root->data.CMND)
    {
        root->left = insert(root->left, hk);
    }
    else
    {
        root->right = insert(root->right, hk);
    }

    return root;
}

void inOrderTraversal(Node *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left);
        cout << "CMND: " << root->data.CMND;
        cout << "\nHo: " << root->data.ho;
        cout << "\nTen: " << root->data.ten;
        cout << "\nPhai: " << root->data.phai;
        inOrderTraversal(root->right);
    }
}

Node *searchByCMND(Node *root, string cmnd)
{
    if (root != NULL)
    {
        if (cmnd == root->data.CMND)
        {
            return root;
        }
        else if (cmnd < root->data.CMND)
        {
            return searchByCMND(root->left, cmnd);
        }
        else
        {
            return searchByCMND(root->right, cmnd);
        }
    }

    return NULL;
}