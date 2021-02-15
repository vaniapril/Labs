#include "Fraction.h"
#include <assert.h>
#include <iostream>

Fraction::Fraction(int numerator, int denominator){
    _numerator = numerator;
    assert(denominator != 0);
    _denominator = denominator;
    _reduce();
}
Fraction::Fraction(int numerator){
    _numerator = numerator;
    _denominator = 1;
}
Fraction::Fraction(Fraction &fraction){
    _denominator = fraction.getDenominator();
    _numerator = fraction.getNumerator();
}

void Fraction::_reduce() {
    if(_denominator < 0){
        _denominator *= -1;
        _numerator *= -1;
    }
    for(int i = _denominator;i > 1;i --){
        if((_numerator % i == 0) && (_denominator % i == 0)){
            _numerator /= i;
            _denominator /= i;
            break;
        }
    }
}

int Fraction::getNumerator(){
    return _numerator;
}
int Fraction::getDenominator(){
    return _denominator;
}

Fraction Fraction::sum(Fraction f){
    return Fraction(_numerator*f._denominator + _denominator*f._numerator,_denominator*f._denominator);
}
Fraction Fraction::mult(Fraction f){
    return Fraction(_numerator*f._numerator,_denominator*f._denominator);
}
Fraction Fraction::div(Fraction f){
    return Fraction(_numerator*f._denominator,_denominator*f._numerator);
}

void Fraction::print(){
    if(_denominator == 1){
        std::cout<< _numerator;
    } else {
        if(_numerator == 0){
            std::cout<<0;
        } else {
            if (_numerator > 0){
                if(_numerator / _denominator != 0){
                    std::cout<<_numerator / _denominator<<' '<< _numerator % _denominator << '/' << _denominator;
                } else {
                    std::cout<<_numerator << '/'<<_denominator;
                }
            } else {
                if(-(_numerator / _denominator) != 0){
                    std::cout<<_numerator / _denominator<<' '<< (-_numerator) % _denominator << '/' << _denominator;
                } else {
                    std::cout<<_numerator << '/'<<_denominator;
                }
            }
        }
    }
    std::cout<< '\n';
}