#include "include/Vector.h"
#include <cmath>
#define M_PI 3.14159265358979323846

Vector::Vector(Number x, Number y) :_x(x), _y(y) {}

Number Vector::r()
{
	Number num = _x * _x + _y * _y;
	return createNumber(sqrt(num.getValue()));
}

Number Vector::fi()
{
	if (_x.getValue() == 0) {
		if (_y.getValue() > 0) {
			return createNumber(M_PI / 2);
		}
		if (_y.getValue() < 0) {
			return createNumber(- M_PI / 2);
		}
	} else {
		Number num = _y / _x;
		num = createNumber(atan(num.getValue()));
		if (_x.getValue() > 0) {
			return num;
		}
		if (_x.getValue() < 0 && _y.getValue() >= 0) {
			return num + createNumber(M_PI);
		}
		if (_x.getValue() < 0 && _y.getValue() < 0) {
			return num - createNumber(M_PI);
		}
	}
	return zero;
}

Vector Vector::sum(Vector v)
{
	return Vector(_x + v._x, _y + v._y);
}
