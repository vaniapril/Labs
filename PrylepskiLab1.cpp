// 5
#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int k;
	double k2,x,ln,ln2,addLn;
	
	cout<< "X (-1;1]: ";
	cin>> x;
	cout<< "K : ";
	cin>> k;
	ln = 0;
	k2 = pow(10,-k);

	for(int i = 1;;i++){
		addLn = pow(x,i)/i;
		if(addLn <= k2){
			break;
		}
		ln += pow(-1,i + 1)*addLn;	
	}
	
	cout.precision(k);
	
	ln2 = log(1 + x);
	cout<< "ln(1 + x) : "<< '\n' << ln << '\n' << ln2;
	return 0;
}
