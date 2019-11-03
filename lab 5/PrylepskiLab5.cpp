#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// 5 вариант
using namespace std;

void show_file(string name){
    cout<<name << ":\n=============\n";
    ifstream in(name);
    while(!in.eof()){
        char c = in.get();
        cout<< c;
    }
    in.close();
    cout<<"\n=============\n";
}

void write_file(string name, vector<string> strs){
    vector<string> old_strs;
    ifstream in(name);
    if(in){
        while(!in.eof()){
            string str;
            getline(in,str,'\n');
            if (str.size() != 0) {
                old_strs.push_back(str);
            }
        }
    }
    in.close();

    ofstream out(name);
    for(string str : old_strs){
        out<< str;
        out<<'\n';
    }
    for(int i = 0; i < strs.size() - 1; i++){
        out<< strs[i];
        out<<'\n';
    }
    if(strs.size() != 0){
        out<<strs[strs.size() - 1];
    }
    out.close();
}

vector<string> read_file(string name){
    vector<string> strs;
    ifstream in(name);
    while(!in.eof()){
        string str;
        getline(in,str,'\n');
        if (str.size() != 0) {
            strs.push_back(str);
        }
    }
    in.close();
    return strs;
}

string file_name(string mesage, string default_name){
    while(true){
        cout<< mesage<<"\n1. Default("<< default_name<< ").\n2. From console.\n";
        int n;
        cin>> n;
        if(n == 1){
            return default_name;
        }
        if(n == 2){
            string str;
            cout<< "Enter file name: ";
            cin>> str;
            return str;
        }
    }
}

vector<string> palindromes(vector<string> strs){
    vector<string> pal;
    for(string str : strs){
        bool is_pal = true;
        for(int i = str.length() / 2; i >= 0; i--){
            if(str[i] != str[str.length() - i - 1]){
                is_pal = false;
                break;
            }
        }
        if(is_pal){
            pal.push_back(str);
        }
    }
    return pal;
}

vector<string> same_symbols(vector<string> strs){
    vector<string> sim;
    for(string str : strs){
        bool is_sim = true;
        char c = str[0];
        for(int i = str.length() - 1; i > 0; i--){
            if(str[i] != c){
                is_sim = false;
                break;
            }
        }
        if(is_sim){
            sim.push_back(str);
        }
    }
    return sim;
}

int main(){
    string name = file_name("File name from", "input.txt");
    show_file(name);
    vector<string> strs = read_file(name);

    string namePal = file_name("File for palindromes","outputPal.txt");
    vector<string> pal = palindromes(strs);
    write_file(namePal,pal);
    show_file(namePal);

    string name_same_symb = file_name("File for lines consisting of the same symbols","outputSim.txt");
    vector<string> same_symb = same_symbols(strs);
    write_file(name_same_symb,same_symb);
    show_file(name_same_symb);
    return 0;
}
