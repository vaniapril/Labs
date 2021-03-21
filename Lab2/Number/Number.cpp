#include "include/Number.h"

Number one(1);
Number zero(0);

Number::Number(double value) :_value(value) {}

Number Number::operator+(Number n)
{
	return Number(_value + n._value);
}

Number Number::operator-(Number n)
{
	return Number(_value - n._value);
}

Number Number::operator*(Number n)
{
	return Number(_value * n._value);
}

Number Number::operator/(Number n)
{
	return Number(_value / n._value);
}

double Number::getValue()
{
	return _value;
}

Number createNumber(double value)
{
	return Number(value);
}
