#ifndef UNTITLED_FRACTION_H
#define UNTITLED_FRACTION_H

class Fraction {
private:
    int _numerator;
    int _denominator;
    Fraction();
    void _reduce();
public:
    Fraction(int numerator, int denominator);
    Fraction(int numerator);
    Fraction(Fraction &fraction);

    int getNumerator();
    int getDenominator();

    Fraction sum(Fraction f);
    Fraction mult(Fraction f);
    Fraction div(Fraction f);
    void print();
};

#endif
