#include <iostream>
using namespace std;

char* new_itoa(int value, char* string, int radix){
	int k;
	char c;
	int i = 0;
	for(; value != 0; i++){
		k = value % radix;
		if(k < 10){
			c = 48 + k;
		} else {
			c = 'A' + k - 10;
		}
		string[i] = c;
		value /= radix;
	}
	for(int i2 = 0; i2 < i/2; i2++){
		c = string[i2];
		string[i2] = string[i - i2 - 1];
		string [i - i2 - 1] = c;
	}
	return string;
};

int main(){
	int value;
	int radix;
	cout<<"Value: ";
	cin>> value;
	cout<<"Radix [2,36]: ";
	cin>> radix;
	if(radix < 2 || radix > 36){
		cout<< "Error: Radix > 36 or < 2 !\n";
		return 0;
	}
	int len = 0;
	for(int v = value;v != 0;len++){
		v /= radix;
	}
	char* str = new char[len];
	str = new_itoa(value,str,radix);
	for(int i = 0; i < len; i++){
		cout<< str[i];
	}
	return 0;
}
