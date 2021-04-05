#include <iostream>
#include "support.h"
#include "task1.h"
#include "task2-1.h"
#include "task2-2.h"

MatrixData *matrixData;
int threadCount;

void read(){
    FILE* in = fopen("input.txt", "r");
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

void write(double **C){
    for (int i = 0; i < matrixData->_m; i++) {
        std::cout<<'\n';
        for (int j = 0; j < matrixData->_n; j++) {
            std::cout<<matrixData->_A[i][j]<<' ';
        }
    }
    std::cout<<'\n';
    for (int i = 0; i < matrixData->_n; i++) {
        std::cout<<'\n';
        for (int j = 0; j < matrixData->_l; j++) {
            std::cout<<matrixData->_B[i][j]<<' ';
        }
    }

    std::cout<<'\n';
    for (int i = 0; i < matrixData->_m; i++) {
        std::cout<<'\n';
        for (int j = 0; j < matrixData->_l; j++) {
            std::cout<<C[i][j]<<' ';
        }
    }
}

int main() {
    read();
    double **C = namespaceTask2_2::task(matrixData, threadCount);
    write(C);
    return 0;
}
