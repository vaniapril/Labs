class Number {
	double _value;
public:
	Number(double value);
	Number operator+(Number n);
	Number operator-(Number n);
	Number operator*(Number n);
	Number operator/(Number n);

	double getValue();
};

extern Number zero;
extern Number one;

Number createNumber(double value);
