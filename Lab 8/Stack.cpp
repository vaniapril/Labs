#include "Stack.h"

template <typename T>
Stack<T>::Stack(int length) : _length(length), _head(0){
    assert(length > 0);
    stackArray = new T[length];
}
template <typename T>
Stack<T>::Stack(std::initializer_list<T> list) : Stack(list.size() * 2){
    for(T i : list){
        push(i);
    }
}
template <typename T>
Stack<T>::Stack() : Stack(10){}

template <typename T>
T Stack<T>::pop(){
    assert(_head != 0);
    return stackArray[--_head];
}
template <typename T>
void Stack<T>::push(const T &element){
    if (_head == _length){
        T* newArr = new T[_length * 2];
        for(int i = 0; i < _length; i++){
            newArr[i] = stackArray[i];
        }
        delete [] stackArray;
        stackArray = newArr;
        _length *= 2;
    }
    stackArray[_head++] = element;
}
template <typename T>
int Stack<T>::size() const{
    return _head;
}
template <typename T>
bool Stack<T>::isEmpty() const{
    return _head == 0;
}

template <typename T>
void Stack<T>::remove(int i){
    assert(i >= 0 && i < size());
    while(i > 0){
        stackArray[_head - i - 1] = stackArray[_head - i];
        i--;
    }
    _head--;
}
template <typename T>
void Stack<T>::operator<<(const T &element){
    push(element);
}
template <typename T>
void Stack<T>::operator>>(T &element){
    element = pop();
}
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T> &stack){
    if(_length != stack._length){
        delete [] stackArray;
        _length = stack._length;
        stackArray = new T[_length];
    }
    _head = 0;
    for(int i = 0; i < stack._head; i++){
        push(stack.stackArray[i]);
    }
    return *this;
}
template <typename T>
T& Stack<T>::operator[](int index){
    assert(index >= 0);
    assert(index < _head);
    return stackArray[_head - index - 1];
};
template <typename T>
bool Stack<T>::operator==(const Stack<T> &stack){
    if(size() == stack.size()){
        for(int i = 0; i < size();i++){
            if(stackArray[i] != stack.stackArray[i]){
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}
template <typename T>
bool Stack<T>::operator!=(const Stack<T> &stack){
    return !(*this == stack);
};
template <typename T>
bool Stack<T>::operator<(const Stack<T> &stack){
    if(size() == stack.size()){
        for(int i = 0; i < size();i++){
            if(stackArray[i] != stack.stackArray[i]){
                return stackArray[i] < stack.stackArray[i];
            }
        }
        return false;
    } else {
        return size() < stack.size();
    }
}
template <typename T>
bool Stack<T>::operator>(const Stack<T> &stack){
    if(size() == stack.size()){
        for(int i = 0; i < size();i++){
            if(stackArray[i] != stack.stackArray[i]){
                return stackArray[i] > stack.stackArray[i];
            }
        }
        return false;
    } else {
        return size() > stack.size();
    }
}
template <typename T>
Stack<T>::~Stack(){
    delete [] stackArray;
}

template class Stack<double>;
template class Stack<string>;
template class Stack<int>;