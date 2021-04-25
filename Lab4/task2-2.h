#ifndef LAB3_TASK2_2_H
#define LAB3_TASK2_2_H

#include <iostream>
#include "data.h"
#include "matrix.h"

namespace namespaceTask2_2{
    class ParamChannel{
        int _n;
        int currentI;

        HANDLE mutex;
    public:
        ParamChannel(int n){
            _n = n;
            currentI = 0;
            mutex = CreateMutex(NULL, FALSE, "Param");
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

    ParamChannel *paramChannel;
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
        paramChannel = new ParamChannel(data->_n);
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

#endif //LAB3_TASK2_2_H
