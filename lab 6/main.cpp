#include "Fraction.h"

using namespace std;

int main() {
    //Создание дробей
    Fraction f1(3,4), f2(5), f3(f1), f4(8,-20);
    f1.print();//конструктор по числителю и знаменателю
    f2.print();//конструктор только по числителю
    f3.print();//конструктор копирования
    f4.print();//конструктор сокращения
    //сложение
    Fraction sum = f1.sum(f4);
    //Умножение
    Fraction mult = f1.mult(f4);
    //Деление
    Fraction div = f1.div(f4);
    sum.print();
    mult.print();
    div.print();

    //ввод 0 в знаменатель
    //Fraction f0(1,0);

    return 0;
}