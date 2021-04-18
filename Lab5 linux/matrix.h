#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H

#include <pthread.h>

//Создание матрицы
double** createMatrix(int m, int n){
    double **matrix = new double*[m];
    for (int i = 0; i < m; i++) {
        matrix[i] = new double[n];
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

//Удаление матрицы
void deleteMatrix(double **matrix, int m){
    for (int i = 0; i < m; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

//Умножение блоков в матрицах
double** mult(double** A, double** B, int startARow, int startACol, int startBRow, int startBCol, int m, int n, int l){
    double **C = createMatrix(m,l);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < l; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i + startARow][k + startACol] * B[k + startBRow][j + startBCol];
            }
        }
    }
    return C;
}

//Добавление элементов матрицы в блок другой матрицы
void addBlockTo(double** from, double** to, int startRow, int startCol, int m, int n){
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            to[i + startRow][j + startCol] += from[i][j];
        }
    }
}

//класс собирающий матрицу из блоков
class MatrixChannel{
    double** result;
    int _n;
    int _m;
    pthread_mutex_t mutex;
public:
    MatrixChannel(int m, int n){
        _m = m;
        _n = n;
        result = createMatrix(m,n);
    }

    void addBlock(double** from, int startRow, int startCol, int m, int n){
        pthread_mutex_lock(&mutex);
        addBlockTo(from,result,startRow,startCol,m,n);
        pthread_mutex_unlock(&mutex);
    }

    double** getResult(){
        return result;
    }
};
#endif //LAB3_MATRIX_H
