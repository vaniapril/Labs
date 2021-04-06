#ifndef LAB3_TASK1_H
#define LAB3_TASK1_H

#include "data.h"
#include "matrix.h"

namespace namespaceTask1{
    double** task(MatrixData *matrixData){
        return mult(matrixData->_A, matrixData->_B, 0, 0, 0, 0, matrixData->_m, matrixData->_n, matrixData->_l);
    }
}

#endif //LAB3_TASK1_H
