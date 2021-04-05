#ifndef LAB3_SUPPORT_H
#define LAB3_SUPPORT_H
#include <Windows.h>
#include <iostream>

//Создание/удаление матрицы
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

//класс синхроннизированно выдающий два параметра в пределах от 0 до m и от 0 до n
//вспомогательная структура
struct Params{
    int _i;
    int _j;
    Params(int i, int j){
        _i = i;
        _j = j;
    }
};
//класс
class DoubleParamChannel{
    int _m;
    int _n;

    int currentI;
    int currentJ;

    HANDLE mutex;
public:
    DoubleParamChannel(int m, int n){
        _m = m;
        _n = n;
        currentI = 0;
        currentJ = 0;
        mutex = CreateMutex(NULL, FALSE, "DoubleParam");
    }

    std::pair<Params*,bool> getParam(){
        if(mutex != NULL) WaitForSingleObject(mutex, INFINITE);
        if (currentJ == _n) {
            currentI++;
            currentJ = 0;
        }
        if (currentI == _m){
            ReleaseMutex(mutex);
            return std::pair<Params*,bool>(nullptr, false);
        }
        Params *param = new Params(currentI, currentJ);
        currentJ++;
        ReleaseMutex(mutex);
        return std::pair<Params*,bool>(param, true);
    }
};

//класс
class SingleParamChannel{
    int _n;
    int currentI;

    HANDLE mutex;
public:
    SingleParamChannel(int n){
        _n = n;
        currentI = 0;
        mutex = CreateMutex(NULL, FALSE, "SingleParam");
    }

    std::pair<int, bool> getParam(){
        if(mutex != NULL) WaitForSingleObject(mutex, INFINITE);
        if (currentI == _n){
            ReleaseMutex(mutex);
            return std::pair<int, bool>(0, false);
        }
        ReleaseMutex(mutex);
        return std::pair<int, bool>(currentI++, true);
    }
};

//структура с матрицами и размерами
struct MatrixData{
    double **_A;
    double **_B;
    int _m;
    int _n;
    int _l;

    MatrixData(double **A, double **B, int m, int n, int l){
        _A = A;
        _B = B;
        _m = m;
        _n = n;
        _l = l;
    }
};

//класс собирающий матрицу из блоков
class MatrixChannel{
    double** result;
    int _n;
    int _m;
    HANDLE mutex;
public:
    MatrixChannel(int m, int n){
        _m = m;
        _n = n;
        result = createMatrix(m,n);
        mutex = CreateMutex(NULL, FALSE, "Summer");
    }

    void addBlock(double** from, int startRow, int startCol, int m, int n){
        if(mutex != NULL) WaitForSingleObject(mutex, INFINITE);
        addBlockTo(from,result,startRow,startCol,m,n);
        ReleaseMutex(mutex);
    }

    double** getResult(){
        return result;
    }
};

#endif //LAB3_SUPPORT_H
