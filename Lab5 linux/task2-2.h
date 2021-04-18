#ifndef LAB3_TASK2_2_H
#define LAB3_TASK2_2_H

#include <iostream>
#include "data.h"
#include "matrix.h"

namespace namespaceTask2_2{
    class ParamChannel{
        int _n;
        int currentI;
        pthread_mutex_t mutex;
    public:
        ParamChannel(int n){
            _n = n;
            currentI = 0;
        }

        std::pair<int, bool> getParam(){
            pthread_mutex_lock(&mutex);
            if (currentI == _n){
                pthread_mutex_unlock(&mutex);
                return std::pair<int, bool>(0, false);
            }
            pthread_mutex_unlock(&mutex);
            return std::pair<int, bool>(currentI++, true);
        }
    };

    ParamChannel *paramChannel;
    MatrixData *data;
    MatrixChannel *matrixChannel;

    void* threadProc(void *args){
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
        pthread_exit(0);
    }

    double** task(MatrixData *matrixData, int threadCount) {
        data = matrixData;
        matrixChannel = new MatrixChannel(data->_m, data->_l);
        paramChannel = new ParamChannel(data->_n);

        pthread_t tid[threadCount];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        for(int i = 0; i < threadCount; i++){
            pthread_create(&tid[i], &attr, threadProc, NULL);
        }
        for(int i = 0; i < threadCount; i++){
            pthread_join(tid[i],NULL);
        }
        return matrixChannel->getResult();
    }
}

#endif //LAB3_TASK2_2_H
