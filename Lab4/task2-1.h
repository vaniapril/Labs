#ifndef LAB3_TASK2_1_H
#define LAB3_TASK2_1_H

#include <iostream>
#include "data.h"
#include "matrix.h"

namespace namespaceTask2_1{
    struct Params{
        int _i;
        int _j;
        Params(int i, int j){
            _i = i;
            _j = j;
        }
    };
    class ParamsChannel{
        int _m;
        int _n;

        int currentI;
        int currentJ;

        HANDLE mutex;
    public:
        ParamsChannel(int m, int n){
            _m = m;
            _n = n;
            currentI = 0;
            currentJ = 0;
            mutex = CreateMutex(NULL, FALSE, "Param");
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

    double **C;
    ParamsChannel *paramChannel;
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
        paramChannel = new ParamsChannel(data->_m, data->_l);
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
