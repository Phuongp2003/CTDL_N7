#pragma once
#include "hanhkhach.h"
#include "header.h"

class NodeQueue
{
private:
    NodeHK *data;
    NodeQueue *next;

public:
    NodeQueue(NodeHK *data);
    NodeHK *getData();
    void setData(NodeHK *data);
    NodeQueue *getNext();
    void setNext(NodeQueue *next);
};

class Queue
{
private:
    NodeQueue *front;
    NodeQueue *rear;

public:
    Queue();
    NodeHK *getFront();
    void setFront(NodeQueue *front);
    NodeQueue *getRear();
    void setRear(NodeQueue *rear);
    void push(NodeHK *data);
    void pop();
    bool isEmpty();
};
