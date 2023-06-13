#include "../header/queue.h"

NodeQueue::NodeQueue(NodeHK *data)
{
    this->data = data;
    this->next = NULL;
}

NodeHK *NodeQueue::getData()
{
    return this->data;
}

NodeQueue *NodeQueue::getNext()
{
    return this->next;
}

void NodeQueue::setData(NodeHK *data)
{
    this->data = data;
}

void NodeQueue::setNext(NodeQueue *next)
{
    this->next = next;
}

//-----------------------------

Queue::Queue()
{
    this->front = NULL;
    this->rear = NULL;
}

void Queue::setFront(NodeQueue *front)
{
    this->front = front;
}

NodeQueue *Queue::getRear()
{
    return this->rear;
}

void Queue::setRear(NodeQueue *rear)
{
    this->rear = rear;
}

void Queue::push(NodeHK *data)
{
    NodeQueue *tmp = new NodeQueue(data);

    if (rear == NULL)
    {
        this->front = tmp;
        this->rear = tmp;
        return;
    }
    this->rear->setNext(tmp);
    this->rear = tmp;
}

void Queue::pop()
{
    if (this->front == NULL)
    {
        return;
    }
    NodeQueue *tmp = this->front;
    this->front = this->front->getNext();

    if (this->front == NULL)
    {
        this->rear = NULL;
    }
    delete tmp;
    tmp = 0;
}

NodeHK *Queue::getFront()
{
    return this->front->getData();
}

bool Queue::isEmpty()
{
    return this->front == NULL;
}
