#include "Queue.h"

template<class T>
Queue<T>::Queue():_size(0), in(nullptr), out(nullptr){}
template<class T>
void Queue<T>::push(T data){
    if(_size == 0){
        QueueNode* node = new QueueNode(data);
        out = node;
        in = node;     } else {
        QueueNode* node = new QueueNode(data);
        in->next = node;
        in = node;
    }
    _size++;
}
template<class T>
void Queue<T>::pushBack(T data){
    if(_size == 0){
        QueueNode* node = new QueueNode(data);
        out = node;
        in = node;
    } else {
        QueueNode* node = new QueueNode(data);
        node->next = out;
        out = node;
    }
    _size++;
}
template<class T>
T Queue<T>::pop(){
    if(_size <= 0) throw "QueueSize <= 0";
    QueueNode* tmp = out;
    T data = out->_data;
    out = tmp->next;
    delete tmp;
    _size--;
    return data;
}
template<class T>
int Queue<T>::size(){
    return _size;
}
template<class T>
bool Queue<T>::isEmpty(){
    return _size == 0;
}
template<class T>
Queue<T>::~Queue(){
    while(!isEmpty()){
        QueueNode* tmp = out;
        out = tmp->next;
        delete tmp;
        _size--;
    }
}



template class Queue<Element<char>>;