#include "../header/queue.h"

Queue::Queue(int size)
{
    this->size = size;
    arr = new NodeHK *[size];
    this->front = -1;
    this->rear = -1;
}

bool Queue::isEmpty()
{
    return this->front == -1 || this->rear == -1;
}

bool Queue::isFull()
{
    return this->rear - this->front + 1 == 0 || 
        this->rear - this->front + 1 == this->size;
}

void Queue::push(NodeHK *node)
{
    if (isFull())
    {
        return;
    }
    if (this->front == -1) {
        this->front = 0;
        this->rear = -1;
    }
    if (this->rear == this->size - 1) {
        this->rear = -1;
    }
    ++this->rear;
    arr[this->rear] = node;
}

void Queue::pop()
{
    if (isEmpty())
    {
        return;
    }
    if (this->front == this->rear)
    {
        this->front = -1;
        this->rear = -1;
    }
    else
    {
        this->front++;
        if (this->front == this->size) {
            this->front = 0;
        }
    }
}

NodeHK *Queue::getFront()
{
    return arr[this->front];
}