#ifndef LAB8_STACK_H
#define LAB8_STACK_H

#include <assert.h>
#include <iostream>

using namespace std;

template<typename T>
class Stack {
private:
    int _length;
    int _head;
    T* stackArray;
public:
    Stack(int length);
    Stack(std::initializer_list<T> list);
    Stack();

    T pop();
    void push(const T &element);
    int size() const;
    bool isEmpty() const;
    void remove(int i);

    void operator<<(const T &element);
    void operator>>(T &element);
    Stack& operator=(const Stack &stack);
    T& operator[](int index);
    bool operator==(const Stack &stack);
    bool operator!=(const Stack &stack);
    bool operator<(const Stack &stack);
    bool operator>(const Stack &stack);
    ~Stack();
};


#endif //LAB8_STACK_H
