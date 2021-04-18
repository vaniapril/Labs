#ifndef LAB3_TASK2_1_H
#define LAB3_TASK2_1_H

#include <iostream>
#include <wait.h>
#include "data.h"
#include "matrix.h"
#include "unistd.h"
#include "stdio.h"
#include <sys/mman.h>

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

        pthread_mutex_t mutex;
    public:
        ParamsChannel(int m, int n){
            _m = m;
            _n = n;
            currentI = 0;
            currentJ = 0;
        }

        std::pair<Params*,bool> getParam(){
            pthread_mutex_lock(&mutex);
            if (currentJ == _n) {
                currentI++;
                currentJ = 0;
            }
            if (currentI == _m){
                pthread_mutex_unlock(&mutex);
                return std::pair<Params*,bool>(nullptr, false);
            }
            Params *param = new Params(currentI, currentJ);
            currentJ++;
            pthread_mutex_unlock(&mutex);
            return std::pair<Params*,bool>(param, true);
        }
    };

    double **C;
    ParamsChannel *paramChannel;
    MatrixData *data;

    void* threadProc(void *args){
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
        pthread_exit(0);
    }

    double** task(MatrixData *matrixData, int threadCount){
        data = matrixData;
        C = createMatrix(data->_m, data->_l);
        paramChannel = new ParamsChannel(data->_m, data->_l);
        pthread_t tid[threadCount];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        for(int i = 0; i < threadCount; i++){
            pthread_create(&tid[i], &attr, threadProc, NULL);
        }
        for(int i = 0; i < threadCount; i++){
            pthread_join(tid[i],NULL);
        }
        return C;
    }
}

#endif //LAB3_TASK2_1_H
