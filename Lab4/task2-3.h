#ifndef LAB3_TASK2_3_H
#define LAB3_TASK2_3_H

#include <iostream>
#include "data.h"
#include "matrix.h"

namespace namespaceTask2_3{
    struct Blocks{
        int _startARow;
        int _startACol;
        int _startBRow;
        int _startBCol;
        int _m;
        int _n;
        int _l;
        Blocks(int startARow, int startACol, int startBRow, int startBCol, int m, int n, int l){
            _startARow = startARow;
            _startACol = startACol;
            _startBRow = startBRow;
            _startBCol = startBCol;
            _m = m;
            _n = n;
            _l = l;
        }
    };
    class BlocksChannel{
        int _sizeM;
        int _sizeN;
        int _sizeL;
        int _divM;
        int _divN;
        int _divL;
        int _count;

        int currentI;
        int currentJ;
        int currentK;

        HANDLE mutex;
    public:
        BlocksChannel(int m, int n, int l, int count){
            _sizeM = m / count;
            _sizeN = n / count;
            _sizeL = l / count;
            _divM = m % count;
            _divN = n % count;
            _divL = l % count;
            _count = count;
            currentI = 0;
            currentJ = 0;
            currentK = 0;
            mutex = CreateMutex(NULL, FALSE, "Param");
        }

        std::pair<Blocks*,bool> getParam(){
            if(mutex != NULL) WaitForSingleObject(mutex, INFINITE);
            if (currentK == _count) {
                currentJ++;
                currentK = 0;
            }
            if (currentJ == _count) {
                currentI++;
                currentJ = 0;
            }
            if (currentI == _count){
                ReleaseMutex(mutex);
                return std::pair<Blocks*,bool>(nullptr, false);
            }
            Blocks *param = new Blocks(
                    _sizeM * currentI + (currentI > _divM ? _divM : currentI),
                    _sizeN * currentK + (currentK > _divN ? _divN : currentK),
                    _sizeN * currentK + (currentK > _divN ? _divN : currentK),
                    _sizeL * currentJ + (currentJ > _divL ? _divL : currentJ),
                    _sizeM + (currentI < _divM ? 1 : 0),
                    _sizeN + (currentK < _divN ? 1 : 0),
                    _sizeL + (currentJ < _divL ? 1 : 0)
                    );
            currentK++;
            ReleaseMutex(mutex);
            return std::pair<Blocks*,bool>(param, true);
        }
    };

    BlocksChannel *blocksChannel;
    MatrixData *data;
    MatrixChannel *matrixChannel;
    int k;

    DWORD WINAPI threadProc(LPVOID lpParam){
        double **result;
        double **bufferC = createMatrix(data->_m,data->_l);
        std::pair<Blocks*,bool> param;
        while (true){
            param = blocksChannel->getParam();
            if (param.second){
                result = mult(data->_A, data->_B, param.first->_startARow,
                              param.first->_startACol,
                              param.first->_startBRow,
                              param.first->_startBCol,
                              param.first->_m,
                              param.first->_n,
                              param.first->_l);
                addBlockTo(result, bufferC, param.first->_startARow,param.first->_startBCol, param.first->_m, param.first->_l);
                deleteMatrix(result, param.first->_m);
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
        k = threadCount;
        matrixChannel = new MatrixChannel(data->_m, data->_l);
        blocksChannel = new BlocksChannel(data->_m, data->_n, data->_l, threadCount);
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
