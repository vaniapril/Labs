#ifndef KR2_QUEUE_H
#define KR2_QUEUE_H


#include "Element.h"
#include "iostream"

using namespace std;

template <class T>
class Queue{
private:
    class QueueNode{
    public:
        T _data;
        QueueNode* next;
        QueueNode(T data):_data(data._value),next(nullptr){}
    };

    QueueNode* in;
    QueueNode* out;
    int _size;
public:
    Queue();
    void push(T data);
    void pushBack(T data);
    T pop();
    int size();
    bool isEmpty();
    ~Queue();
};


#endif //KR2_QUEUE_H
