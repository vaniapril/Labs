#ifndef LAB3_TASK2_3_H
#define LAB3_TASK2_3_H
#include "support.h"

namespace namespaceTask2_3{
    DoubleParamChannel *paramChannel;
    MatrixData *data;
    MatrixChannel *matrixChannel;

    DWORD WINAPI threadProc(LPVOID lpParam){
        double **result;
        double **bufferC = createMatrix(data->_m,data->_l);
        std::pair<int,bool> param;
        while (true){
            param = paramChannel->getParam();
            if (param.second){
                result = mult(data->_A, data->_B, 0, param.first, param.first, 0, data->_m, 1, data->_l);
                addBlockTo(result, bufferC, 0,0, data->_m, data->_l);
                for (int i = 0; i < data->_m; i++) {
                    std::cout<<'\n';
                    for (int j = 0; j < data->_l; j++) {
                        std::cout<<result[i][j]<<' ';
                    }
                }
                deleteMatrix(result, data->_m);
            } else {
                break;
            }
        }
        matrixChannel->addBlock(bufferC,0,0,data->_m, data->_l);
        deleteMatrix(bufferC, data->_m);
        return 0;
    }

    double** task(MatrixData *matrixData, int threadCount){
        data = matrixData;
        matrixChannel = new MatrixChannel(data->_m, data->_l);
        paramChannel = new DoubleParamChannel(data->_n, data->_n);
        HANDLE *Array_Of_Thread_Handles = new HANDLE[threadCount];
        for(int i = 0; i < threadCount; i++){
            Array_Of_Thread_Handles[i] = CreateThread(NULL, 0, threadProc, NULL , 0, 0);
        }
        WaitForMultipleObjects(threadCount, Array_Of_Thread_Handles, TRUE, INFINITE);
        for(int i = 0; i < threadCount; i++){
            CloseHandle(Array_Of_Thread_Handles[i]);
        }
        return matrixChannel->getResult();
    }
}

#endif //LAB3_TASK2_3_H
