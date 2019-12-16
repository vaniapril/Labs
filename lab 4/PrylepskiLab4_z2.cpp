#include <iostream>
#include <fstream>
using namespace std;

void word(char* str, int n){
	int start_answ_word;
	int start_word = 0;
	int answ_len;
	int len;
	int diff = 0;
	for(;start_word - 1 != n;){
		len = 0;	
		do{
			len++;
		} while (start_word + len != n && str[start_word + len] != ' ');
		
		int d = 1;
		for(int i2 = 1; i2 < len; i2++){
			bool is_diff = true;
			for(int i3 = i2 - 1; i3 >= 0;i3--){
				if(str[start_word + i2] == str[start_word + i3]){
					is_diff = false;
					break;
				}
			}
			if(is_diff){
				d++;
			}
		}

		if(d >= diff){
			start_answ_word = start_word;
			diff = d;
			answ_len = len;
		}
		start_word += (len + 1);
	}
	
	for(int i2 = start_answ_word; i2 < start_answ_word + answ_len; i2++){
		cout<< str[i2];
	}
}

void from_file(char* str){
	ifstream in(str);
	for(int i = 1; !in.eof(); i++){
		int len = 0;
		char* str = new char[300];
		char c = 0;
		while((c = in.get()) != '\n' && c != EOF){
			str[len] = c;
			len++;
		}
		cout<< "String "<< i <<": ";
		word(str,len);
		cout<< ".\n";
	}	
}

void from_console(){
	int len = 0;
	char* str = new char[300];
	cin.ignore();
	char c = 0;
	while((c = cin.get()) != '\n'){
		str[len] = c;
		len++;
	}
	cout<< "Answer: ";
	word(str,len);
	cout<< ".\n";	
}

int main(){
	while(true){
		cout<<"Choose the right option:\n1. From file.\n2. From console.\n";
		int n;
		cin>> n;
		if(n == 1){
			while(true){
				cout<<"Choose the right option:\n1. Default file name(input.txt).\n2. From console.\n";
				cin>> n;
				if(n == 1){
					from_file("input.txt");
				}
				if(n == 2){
					cout<<"Enter file name:\n";
					char* str = new char[300];
					cin>> str;
					from_file(str);
				}
				break;
			}
			break;
		}
		if(n == 2){
			cout<<"Enter a string:\n";
			from_console();
			break;
		}
	}
	
	
}
