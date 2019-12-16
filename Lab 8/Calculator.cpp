#include "Calculator.h"

void Calculator::input(string str){
    _str = str;
}
bool Calculator::isNum(string &num){
    bool answ = false;
    switch(num[0]){
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            answ = true;
            break;
        case '-':
            if(num.size() == 1){
                return false;
            }
            switch(num[1]){
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    answ = true;
                    break;
            }
            break;
    }
    return answ;
}
void Calculator::createPolish(){
    assert(isTrue());
    Stack<string> stack;
    Stack<string> signs;
    _polish = Stack<string>();
    string str;
    while (!_expression.isEmpty()){
        str = _expression.pop();
        if(str == "-" || str == "+"){
            if(!signs.isEmpty()){
                while(signs[0] == "*" || signs[0] == "/" || signs[0] == "+" || signs[0] == "-"){
                    stack<<signs.pop();
                    if(signs.isEmpty()){
                        break;
                    }
                }
            }
            signs<<str;
            continue;
        }
        if(str == "*" || str == "/"){
            if(!signs.isEmpty()){
                while(signs[0] == "*" || signs[0] == "/"){
                    stack<<signs.pop();
                    if(signs.isEmpty()){
                        break;
                    }
                }
            }
            signs<<str;
            continue;
        }
        if(str == "("){
            signs<<str;
            continue;
        }
        if(str == ")"){
            while(signs[0] != "("){
                stack<<signs.pop();
            }
            signs.pop();
            continue;
        }
        stack<<str;
    }
    while (!signs.isEmpty()){
        stack<<signs.pop();
    }
    while (!stack.isEmpty()){
        _polish<<stack.pop();
    }
}
string Calculator::polishToString(){
    Stack<string> polish;
    polish = _polish;
    string answ = polish.pop();
    while (!polish.isEmpty()){
        answ += ' ' + polish.pop();
    }
    return answ;
}
double Calculator::calculate(){
    createPolish();
    string str;
    double num1;
    double num2;
    Stack<double> stack;
    while (!_polish.isEmpty()){
        _polish>>str;
        if(str == "+"){
            num1 = stack.pop();
            num2 = stack.pop();
            stack.push(num2 + num1);
            continue;
        }
        if(str == "-"){
            num1 = stack.pop();
            num2 = stack.pop();
            stack.push(num2 - num1);
            continue;
        }
        if(str == "*"){
            num1 = stack.pop();
            num2 = stack.pop();
            stack.push(num2 * num1);
            continue;
        }
        if(str == "/"){
            num1 = stack.pop();
            num2 = stack.pop();
            stack.push(num2 / num1);
            continue;
        }
        stringstream num;
        num<<str;
        num>>num1;
        stack<<num1;
    }
    return stack.pop();
}
bool Calculator::isTrue(){
    if(_str.size() == 0) {
        return false;
    }
    Stack<string> stack;
    regex r("[+-/*]+|[0123456789.]+|[\\(\\)]");
    sregex_iterator next(_str.begin(), _str.end(),r);
    sregex_iterator end;
    while(next != end){
        smatch match = *next;
        stack<<match[0];
        ++next;
    }
    ;
    _expression = Stack<string>();
    while(!stack.isEmpty()){
        _expression<<stack.pop();
    }
    int parentheses = 0;
    for(int i = 0; i < _expression.size();i++){
        if(_expression[i] == "-" || _expression[i] == "+" || _expression[i] == "/" || _expression[i] == "*"){
            if(i != 0){
                if(!isNum(_expression[i - 1]) && _expression[i - 1] != ")"){
                    if(_expression[i] == "-" && _expression[i - 1] == "("){
                        _expression[i + 1] = "-" + _expression[i + 1];
                        _expression.remove(i);
                        i--;
                        if(_expression[i + 2] == ")"){
                            _expression.remove(i);
                            i--;
                            _expression.remove(i + 2);
                            parentheses--;
                        }
                        continue;
                    } else {
                        return false;
                    }
                }
            } else {
                if(_expression[i] == "-" && isNum(_expression[i + 1])){
                    _expression[i + 1] = "-" + _expression[i + 1];
                    _expression.remove(i);
                    i--;
                } else {
                    cout<<"?????";
                    return false;
                }
                continue;
            }
            if(i != _expression.size() - 1){
                if(!isNum(_expression[i + 1]) && _expression[i + 1] != "("){
                    return false;
                }
            } else {
                return false;
            }
            continue;
        }
        if(_expression[i] == "("){
            parentheses++;
            continue;
        }
        if(_expression[i] == ")"){
            if(--parentheses < 0){
                return false;
            }
            continue;
        }
        if(isNum(_expression[i])){
            if(i != _expression.size() - 1){
                if(isNum(_expression[i + 1])){
                    return false;
                }
            }
        } else{
            return false;
        }
    }
    return parentheses == 0;
}