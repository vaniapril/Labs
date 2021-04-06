#include <iostream>
#include <ctime>
#include <random>
#include "task1.h"
#include "task2-1.h"
#include "task2-2.h"
#include "task2-3.h"

MatrixData *matrixData;
int threadCount;

void read(){
    FILE* in = fopen("..\\input.txt", "r");
    int m;
    int n;
    int l;
    fscanf(in, "%i %i %i", &threadCount, &m, &n);
    double **A = new double *[n];
    for (int i = 0; i < m; i++) {
        A[i] = new double [n];
        for (int j = 0; j < n; j++) {
            fscanf(in, "%lf", &A[i][j]);
        }
    }
    fscanf(in, "%i %i", &n, &l);
    double **B = new double *[n];
    for (int i = 0; i < n; i++) {
        B[i] = new double [l];
        for (int j = 0; j < l; j++) {
            fscanf(in, "%lf", &B[i][j]);
        }
    }
    matrixData = new MatrixData(A, B, m, n, l);
}

bool equals(double **A, double **B){
    bool isEqual = true;
    for (int i = 0; i < matrixData->_m; i++) {
        for (int j = 0; j < matrixData->_l; j++) {
            if (A[i][j] != B[i][j]){
                isEqual = false;
                break;
            }
        }
    }
    return isEqual;
}

int main() {
    read();

    clock_t time1 = clock();
    double **C1 = namespaceTask1::task(matrixData);
    clock_t time2 = clock();
    double **C21 = namespaceTask2_1::task(matrixData, threadCount);
    clock_t time3 = clock();
    double **C22 = namespaceTask2_2::task(matrixData, threadCount);
    clock_t time4 = clock();
    double **C23 = namespaceTask2_3::task(matrixData, threadCount);
    clock_t time5 = clock();

    if(equals(C1, C21) && equals(C21, C22) && equals(C22, C23)){
        std::cout<< "Simple multiplication: " << (double)(time2 - time1) / CLOCKS_PER_SEC << " sec."<<'\n';
        std::cout<< "Multithreaded multiplication (row-column): " << (double)(time3 - time2) / CLOCKS_PER_SEC << " sec."<<'\n';
        std::cout<< "Multithreaded multiplication (column-row) " << (double)(time4 - time3) / CLOCKS_PER_SEC << " sec."<<'\n';
        std::cout<< "Multithreaded multiplication (blocks): " << (double)(time5 - time4) / CLOCKS_PER_SEC << " sec."<<'\n';
    } else {
        std::cout<<"Error";
    }
    return 0;
}
