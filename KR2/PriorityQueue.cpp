#include "PriorityQueue.h"

template <class T>
PriorityQueue<T>::PriorityQueue():_size(0),in(nullptr),out(nullptr){}
template <class T>
void PriorityQueue<T>::insert(T data,int priority){
    if(_size == 0){
        PriorityQueueNode* node = new PriorityQueueNode(data,priority);
        out = node;
        in = node;
    } else {
        if(priority >= out->_priority){
            PriorityQueueNode* node = new PriorityQueueNode(data,priority);
            node->next = out;
            out = node;
        } else {
            PriorityQueueNode* nodeAfter = out;
            int position = _size;
            while (position > 1){
                if(priority < nodeAfter->next->_priority) {
                    nodeAfter = nodeAfter->next;
                    position--;
                } else {
                    break;
                }
            }
            PriorityQueueNode* node = new PriorityQueueNode(data,priority);
            node->next = nodeAfter->next;
            nodeAfter->next = node;
        }
    }
    _size++;
}
template <class T>
T PriorityQueue<T>::pull(){
    if(_size <= 0) throw "QueueSize <= 0";
    PriorityQueueNode* tmp = out;
    T data = out->_data;
    out = tmp->next;
    delete tmp;
    _size--;
    return data;
}
template <class T>
int PriorityQueue<T>::size(){
    return _size;
}
template <class T>
bool PriorityQueue<T>::isEmpty(){
    return _size == 0;
}
template <class T>
PriorityQueue<T>::~PriorityQueue(){
    while(!isEmpty()){
        PriorityQueueNode* tmp = out;
        out = tmp->next;
        delete tmp;
        _size--;
    }
}


template class PriorityQueue<Element<char>>;