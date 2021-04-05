#ifndef LAB3_TASK2_1_H
#define LAB3_TASK2_1_H

#include <Windows.h>
#include <iostream>
#include "support.h"

namespace namespaceTask2_1{
    double **C;
    DoubleParamChannel *paramChannel;
    MatrixData *data;

    DWORD WINAPI threadProc(LPVOID lpParam){
        double **result;
        std::pair<Params*,bool> param;
        while (true){
            param = paramChannel->getParam();
            if (param.second){
                result = mult(data->_A, data->_B, param.first->_i, 0, 0, param.first->_j, 1, data->_n, 1);
                C[param.first->_i][param.first->_j] = result[0][0];
                deleteMatrix(result, 1);
            } else {
                break;
            }
        }
        return 0;
    }

    double** task(MatrixData *matrixData, int threadCount){
        data = matrixData;
        C = createMatrix(data->_m, data->_l);
        paramChannel = new DoubleParamChannel(data->_m, data->_l);
        HANDLE *Array_Of_Thread_Handles = new HANDLE[threadCount];
        for(int i = 0; i < threadCount; i++){
            Array_Of_Thread_Handles[i] = CreateThread(NULL, 0, threadProc, NULL , 0, 0);
        }
        WaitForMultipleObjects(threadCount, Array_Of_Thread_Handles, TRUE, INFINITE);
        for(int i = 0; i < threadCount; i++){
            CloseHandle(Array_Of_Thread_Handles[i]);
        }
        return C;
    }
}

#endif //LAB3_TASK2_1_H
