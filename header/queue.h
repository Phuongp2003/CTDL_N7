#pragma once
#include "header.h"

class Queue
{
private:
    NodeHK **arr;
    int front;
    int rear;
    int size;

public:
    Queue(int size);
    void push(NodeHK *node);
    void pop();
    NodeHK *getFront();
    bool isEmpty();
    bool isFull();
};