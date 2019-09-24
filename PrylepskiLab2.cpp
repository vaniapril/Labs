#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdlib>
using namespace std;

int main(){
	srand(time(NULL));
	int n,A,B,type;
	
	// Filling array
	
	cout<< "Size of array: " << '\n';
	cin>> n;
	if (n <= 0){
		cout<< "Error: Size <= 0 !";
		return 0;
	}
	int m[n];
	cout<< "Type of filling: " << '\n'<<"1. Self"<< '\n'<<"2. Rundom" <<'\n';
	cin>> type;
	
	if(type == 1){
		cout<< "Elements of array: \n";
		for(int i = 0; i < n; i++){
			cin>> m[i];
		}
	} else {
		cout<< "The boundaries of the interval [A,B]: \nA:";
		cin>> A;
		cout<< "B:";
		cin>> B;
		if (A > B){
			cout<< "Error: A > B !\n";
			return 0;
		}
		for(int i = 0; i < n; i++){
			double r = rand();
			r = r/32767 * (B - A + 1);
			m[i] = (int)r + A;
		}
	}
	
	// Number of sign changes
	bool d;
	int k = 0;
	
	if (m[0] >= 0){
		d = true;
	} else{
		d = false;
	}
	
	for(int i = 1; i < n; i++){
		if(d != (m[i] >= 0)){
			k++;
			d  = !d;
		}
	}
	cout<<"Number of sign changes: "<< k<< '\n';
	
	// Multiplication
	int i = 0,s = 1;
	for(;i < n;i++){
		if(m[i] == 0){
			i++;
			break;
		}
	}
	
	for (;;i++){
		if(i >= n){
			cout<< "Error: Two zeros not found. \n";
			break;
		}
		if(m[i] == 0){
			cout<< "Multiplication of elements betwen the first zoro and the second zero: "<< s <<'\n';
			break;
		}
		s *= m[i];
	}

/*	
	cout<< "Array : ";
	for(int i = 0; i < n; i++){
		cout<< m[i] <<";";
	}
*/	
}
