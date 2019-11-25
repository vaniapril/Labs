#ifndef KR2_PRIORITYQUEUE_H
#define KR2_PRIORITYQUEUE_H

#include "iostream"
#include "Element.h"

using namespace std;

template <class T>
class PriorityQueue{
private:
    class PriorityQueueNode{
    public:
        int _priority;
        T _data;
        PriorityQueueNode* next;
        PriorityQueueNode(T data,int priority):_priority(priority),_data(data._value),next(nullptr){}
    };

    PriorityQueueNode* in;
    PriorityQueueNode* out;
    int _size;
public:
    PriorityQueue();
    void insert(T data,int priority);
    T pull();
    int size();
    bool isEmpty();
    ~PriorityQueue();
};

#endif //KR2_PRIORITYQUEUE_H
