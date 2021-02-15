#ifndef LAB8_CALCULATOR_H
#define LAB8_CALCULATOR_H

#include <string>
#include "Stack.h"
#include <sstream>
#include <regex>

using namespace std;

class Calculator {
private:
    string _str;
    Stack<string> _expression;
    Stack<string> _polish;
    bool isNum(string &num);
public:
    void input(string str);
    void createPolish();
    string polishToString();
    double calculate();
    bool isTrue();
};


#endif //LAB8_CALCULATOR_H
