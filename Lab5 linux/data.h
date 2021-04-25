#ifndef LAB3_DATA_H
#define LAB3_DATA_H

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

#endif //LAB3_DATA_H
