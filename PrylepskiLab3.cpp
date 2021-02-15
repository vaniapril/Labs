// 5 вариант
#include <iostream>
#include <vector>

using namespace std;


void rand_matrix(int n, int** matrix){
    for(int xi = 0; xi < n;xi++){
        for(int yi = 0; yi < n;yi++){
            if (xi > yi){
                matrix[xi][yi] = matrix[yi][xi];
            } else {
                matrix[xi][yi] = rand() % 90 + 10;
            }
        }
    }
}

void in_matrix(int n, int** matrix){
    for(int xi = 0; xi < n;xi++){
        for(int yi = 0; yi < n;yi++){
            if (xi > yi){
                matrix[xi][yi] = matrix[yi][xi];
            } else {
            	cout<<"("<< xi <<","<< yi <<") :";
            	cin>> matrix[xi][yi];
            }
        }
    }
}

void out_matrix(int n, int** matrix){
	cout<< "Matrix:\n";
    for(int yi = 0; yi < n;yi++){
        for(int xi = 0; xi < n;xi++){
            cout<< matrix[xi][yi] << ' ';
        }
        cout<< '\n';
    }
}

int** create_matrix(int n){
	int** matrix = new int*[n];
    for(int i = 0; i < n; i++){
        matrix[i] = new int[n];
    }
    return matrix;
}

int size_matrix(){
	int n;
	for(;;){
		cout<< "Size of matrix: \n";
		cin>> n;
		if((n > 10) || (n < 1)){
			cout<< "Error: size > 10 or size < 1\n";
		} else {
			return n;
		}
	}
}

bool is_localMax(int n,int** &matrix,int x,int y){
	if(x - 1 >= 0){
		if (matrix[x][y] <= matrix[x-1][y]){
			return false;
		}
	}
	if(x + 1 < n){
		if (matrix[x][y] <= matrix[x+1][y]){
			return false;
		}
	}
	if(y - 1 >= 0){
		if (matrix[x][y] <= matrix[x][y-1]){
			return false;
		}
	}
	if(y + 1 < n){
		if (matrix[x][y] <= matrix[x][y+1]){
			return false;
		}
	}
	return true;
}

void max_localMax(int n,int** matrix){
	int lx,ly,localMax;
	bool is_exist = false;
	for(int x = 0; x < n; x++){
		for(int y = 0; y < n - x; y++){
		    if(is_localMax(n,matrix,x,y)){
		        if(!is_exist){
		            localMax = matrix[x][y];
		            is_exist = true;
		        }
		        if(matrix[x][y] >= localMax){
		            localMax = matrix[x][y];
		            lx = x;
		            ly = y;
		        }
		    }
		}
	}
	if(is_exist){
	    cout<< "Max Local max: " << localMax <<", in ("<< lx <<";" << ly <<")\n";
	} else {
        cout<< "Local max is no exist!\n";
	}
}

void mult(int n,int** matrix){
	int mult = 1;
	for(int y = n-1; y > 0 ; y--){
		for(int x = n-1; x >= n - y; x--){
			mult *= matrix[x][y];
		}
	}
	cout<< "Multiplication of elements below the secondary diagonal of the matrix, not including the diagonal: "<< mult <<'\n';
}

int main(){
    int n = size_matrix();
    int** matrix = create_matrix(n);
    in_matrix(n,matrix);
//    rand_matrix(n, matrix);
//    out_matrix(n, matrix);
    max_localMax(n,matrix);
    mult(n,matrix);
}
