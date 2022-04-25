#include "functions.h"
#include "MatrixMulFunctions.h"
#include "MatrixMulSwitch.h"
#include <omp.h>

int MatrixMulTime(int func, 
                  float *A, 
                  float *B, 
                  float *C, 
                  int sizeM, 
                  int sizeN, 
                  int sizeK, 
                  int blockSizeM, 
                  int blockSizeN, 
                  int blockSizeK, 
                  int threadsNum, 
                  int N) {
    timespec start, end, timeC;
    double time_in_seconds = 0.0, omp_start, omp_end;
    u_int64_t tacts = 0,
        tacts_theoretical = 0;
    float performance = 0.0;
    Processor i7_4790K;
    i7_4790K.clock = 4e9;
    i7_4790K.clockBoost = 4.4e9;
    i7_4790K.sizeCacheL1 = 128e3;
    i7_4790K.sizeCacheL2 = 1e6;
    i7_4790K.sizeCacheL3 = 8e6;
    Processor i5_9600KF;
    i5_9600KF.clock = 3.7e9;
    i5_9600KF.clockBoost = 4.6e9;
    i5_9600KF.sizeCacheL1 = 192e3;
    i5_9600KF.sizeCacheL2 = 1.5e6;
    i5_9600KF.sizeCacheL3 = 9e6;
    Processor curProcessor = i7_4790K;
    float *At = new float[sizeM * sizeN];
    int threadsCols = 0,
        threadsRows = 0;
    MatrixTranspose(in A, out At, sizeM, sizeN);
    switch (func) {
        case (FuncMatrixMul):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            MatrixMul(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncMatrixMul1):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            MatrixMul1(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncMatrixMulTest):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            MatrixMulTest(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMul):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            AsmMatrixMul(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulN):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMul(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            timeC = diff(start, end);
            time_in_seconds = (static_cast<double>(timeC.tv_sec) + static_cast<double>(timeC.tv_nsec) / 1.0e9) / static_cast<double>(N);
            //printf("%f sec\n", time_in_seconds);
            tacts = time_in_seconds * curProcessor.clock;
            tacts_theoretical = sizeM * sizeN * sizeK / 8;
            performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
            // printf("%d tacts\n", tacts);
            // printf("%d tacts theoretical\n", tacts_theoretical);
            // printf("%f %% performance\n\n", performance * 100);
            printf("%f\n", performance * 100);
            //MatrixPrint(C, sizeM * sizeK, sizeK);
            break;
        case (FuncAsmMatrixMulV2):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            AsmMatrixMulV2(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulV2N):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMulV2(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            timeC = diff(start, end);
            time_in_seconds = (static_cast<double>(timeC.tv_sec) + static_cast<double>(timeC.tv_nsec) / 1.0e9) / static_cast<double>(N);
            //printf("%f sec\n", time_in_seconds);
            tacts = time_in_seconds * curProcessor.clock;
            tacts_theoretical = sizeM * sizeN * sizeK / 16;
            performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
            // printf("%d tacts\n", tacts);
            // printf("%d tacts theoretical\n", tacts_theoretical);
            // printf("%f %% performance\n\n", performance * 100);
            printf("%f\n", performance * 100);
            //MatrixPrint(C, sizeM * sizeK, sizeK);
            break;
        case (FuncAsmMatrixMulV3):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            AsmMatrixMulV3(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulV3N):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMulV3(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            timeC = diff(start, end);
            time_in_seconds = (static_cast<double>(timeC.tv_sec) + static_cast<double>(timeC.tv_nsec) / 1.0e9) / static_cast<double>(N);
            //printf("%f sec\n", time_in_seconds);
            tacts = time_in_seconds * curProcessor.clock;
            tacts_theoretical = sizeM * sizeN * sizeK / 16;
            performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
            // printf("%d tacts\n", tacts);
            // printf("%d tacts theoretical\n", tacts_theoretical);
            // printf("%f %% performance\n\n", performance * 100);
            printf("%f\n", performance * 100);
            //MatrixPrint(C, sizeM * sizeK, sizeK);
            break;
        case (FuncAsmMatrixMulV4):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            AsmMatrixMulV4(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulV4N):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMulV4(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            timeC = diff(start, end);
            time_in_seconds = (static_cast<double>(timeC.tv_sec) + static_cast<double>(timeC.tv_nsec) / 1.0e9) / static_cast<double>(N);
            //printf("%f sec\n", time_in_seconds);
            tacts = time_in_seconds * curProcessor.clock;
            tacts_theoretical = sizeM * sizeN * sizeK / 8;
            performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
            // printf("%d tacts\n", tacts);
            // printf("%d tacts theoretical\n", tacts_theoretical);
            // printf("%f %% performance\n\n", performance * 100);
            printf("%f\n", performance * 100);
            //MatrixPrint(C, sizeM * sizeK, sizeK);
            break;
        case (FuncAsmMatrixMulV5):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            AsmMatrixMulV5(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulV5N):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMulV5(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            timeC = diff(start, end);
            time_in_seconds = (static_cast<double>(timeC.tv_sec) + static_cast<double>(timeC.tv_nsec) / 1.0e9) / static_cast<double>(N);
            //printf("%f sec\n", time_in_seconds);
            tacts = time_in_seconds * curProcessor.clock;
            tacts_theoretical = sizeM * sizeN * sizeK / 16;
            performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
            // printf("%d tacts\n", tacts);
            // printf("%d tacts theoretical\n", tacts_theoretical);
            // printf("%f %% performance\n\n", performance * 100);
            printf("%f\n", performance * 100);
            //MatrixPrint(C, sizeM * sizeK, sizeK);
            break;
        case (FuncAsmMatrixMulBlockV5):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            AsmMatrixMulBlockV5(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulBlockV5N):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMulBlockV5(in A, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            timeC = diff(start, end);
            time_in_seconds = (static_cast<double>(timeC.tv_sec) + static_cast<double>(timeC.tv_nsec) / 1.0e9) / static_cast<double>(N);
            //printf("%f sec\n", time_in_seconds);
            tacts = time_in_seconds * curProcessor.clock;
            tacts_theoretical = sizeM * sizeN * sizeK / 16;
            performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
            // printf("%d tacts\n", tacts);
            // printf("%d tacts theoretical\n", tacts_theoretical);
            // printf("%f %% performance\n\n", performance * 100);
            printf("%f\n", performance * 100);
            //MatrixPrint(C, sizeM * sizeK, sizeK);
            break;
        case (FuncAsmMatrixMulV6):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            AsmMatrixMulV6(in At, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulV6N):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMulV6(in At, in B, out C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            timeC = diff(start, end);
            time_in_seconds = (static_cast<double>(timeC.tv_sec) + static_cast<double>(timeC.tv_nsec) / 1.0e9) / static_cast<double>(N);
            //printf("%f sec\n", time_in_seconds);
            tacts = time_in_seconds * curProcessor.clock;
            tacts_theoretical = sizeM * sizeN * sizeK / 16;
            performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
            // printf("%d tacts\n", tacts);
            // printf("%d tacts theoretical\n", tacts_theoretical);
            // printf("%f %% performance\n\n", performance * 100);
            printf("%f\n", performance * 100);
            //MatrixPrint(C, sizeM * sizeK, sizeK);
            break;
        case (FuncAsmMatrixMulBlockV6):
            // if (sizeM % blockSizeM != 0) 
            //     exit(0); //blockSizeM -= sizeM % blockSizeM;   
            // if (sizeN % blockSizeN != 0) 
            //     exit(0); //blockSizeN -= sizeN % blockSizeN;  
            // if (sizeK % blockSizeK != 0) 
            //     exit(0); //blockSizeK -= sizeK % blockSizeK; 
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            AsmMatrixMulBlockV6(in At, in B, out C, sizeM, sizeN, sizeK, blockSizeM, blockSizeN, blockSizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulBlockV6N):
            // if (sizeM % blockSizeM != 0) 
            //     exit(0); //blockSizeM -= sizeM % blockSizeM;   
            // if (sizeN % blockSizeN != 0) 
            //     exit(0); //blockSizeN -= sizeN % blockSizeN;  
            // if (sizeK % blockSizeK != 0) 
            //     exit(0); //blockSizeK -= sizeK % blockSizeK; 
            // if (sizeM % blockSizeM != 0) 
            //     blockSizeM -= sizeM % blockSizeM;   
            // if (sizeN % blockSizeN != 0) 
            //     blockSizeN -= sizeN % blockSizeN;  
            // if (sizeK % blockSizeK != 0) 
            //     blockSizeK -= sizeK % blockSizeK; 
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMulBlockV6(in At, in B, out C, sizeM, sizeN, sizeK, blockSizeM, blockSizeN, blockSizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            timeC = diff(start, end);
            time_in_seconds = (static_cast<double>(timeC.tv_sec) + static_cast<double>(timeC.tv_nsec) / 1.0e9) / static_cast<double>(N);
            //printf("%f sec\n", time_in_seconds);
            tacts = time_in_seconds * curProcessor.clock;
            tacts_theoretical = sizeM * sizeN * sizeK / 16;
            performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
            // printf("%d tacts\n", tacts);
            // printf("%d tacts theoretical\n", tacts_theoretical);
            // printf("%f %% performance\n\n", performance * 100);
            printf("%f\n", performance * 100);
            //MatrixPrint(C, sizeM * sizeK, sizeK);
            break;
        case (FuncAsmMatrixMulParallelV6):
            // if (sizeM % blockSizeM != 0) 
            //     exit(0); //blockSizeM -= sizeM % blockSizeM;   
            // if (sizeN % blockSizeN != 0) 
            //     exit(0); //blockSizeN -= sizeN % blockSizeN;  
            // if (sizeK % blockSizeK != 0) 
            //     exit(0); //blockSizeK -= sizeK % blockSizeK; 
            if (blockSizeM < threadsNum * threadsNum || blockSizeK < threadsNum * threadsNum) {
                blockSizeM = threadsNum;
                blockSizeK = threadsNum;
                threadsRows = 4;
                threadsCols = 2;
            }
            else {
                blockSizeM /= threadsNum;
                blockSizeK /= threadsNum;
                threadsCols = 4;
                threadsRows = 2;
            }
            if (blockSizeM % 8 != 0 || blockSizeK % 8 != 0)
                exit(0);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            AsmMatrixMulParallelV6(in At, in B, out C, sizeM, sizeN, sizeK, blockSizeM, blockSizeN, blockSizeK, threadsNum, threadsCols, threadsRows);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulParallelV6N):
            // if (sizeM % blockSizeM != 0) 
            //     exit(0); //blockSizeM -= sizeM % blockSizeM;   
            // if (sizeN % blockSizeN != 0) 
            //     exit(0); //blockSizeN -= sizeN % blockSizeN;  
            // if (sizeK % blockSizeK != 0) 
            //     exit(0); //blockSizeK -= sizeK % blockSizeK; 
            // if (sizeM % blockSizeM != 0) 
            //     blockSizeM -= sizeM % blockSizeM;   
            // if (sizeN % blockSizeN != 0) 
            //     blockSizeN -= sizeN % blockSizeN;  
            // if (sizeK % blockSizeK != 0) 
            //     blockSizeK -= sizeK % blockSizeK; 
            //printf("%d | %d | %d\n", blockSizeM, blockSizeN, blockSizeK);
            // if (blockSizeM < threadsNum * threadsNum) {
            //     blockSizeK /= (threadsNum * threadsNum);
            //     threadsCols = 1;
            //     threadsRows = 8;
            // }
            // else if (blockSizeM < threadsNum * threadsNum / 2) {
            //     blockSizeK /= (threadsNum * threadsNum / 2);
            //     threadsCols = 1;
            //     threadsRows = 8;
            // }
            // else if (blockSizeK < threadsNum * threadsNum) {
            //     blockSizeM /= (threadsNum * threadsNum);
            //     threadsCols = 8;
            //     threadsRows = 1;
            // }
            // else if (blockSizeK < threadsNum * threadsNum / 2) {
            //     blockSizeM /= (threadsNum * threadsNum / 2);
            //     threadsCols = 8;
            //     threadsRows = 1;
            // }
            // if (blockSizeM < threadsNum * threadsNum || blockSizeK < threadsNum * threadsNum) {
            //     blockSizeM = threadsNum;
            //     blockSizeK = threadsNum;
            //     threadsRows = 1;//4;
            //     threadsCols = 8;//2;
            // }
            // else {
            //     threadsCols = 1;//4;
            //     threadsRows = 8;//2;
            //     // blockSizeM /= 8;
            //     // blockSizeK /= 8;
            //     //blockSizeM = (sizeM % 128 == 0) ? (sizeM == 128) ? p2(4) : sizeM / threadsNum : p2(3);//p2(5);
            //     blockSizeM = (sizeM % 128 != 0) ? p2(3) : (sizeM == 128) ? p2(4) : p2(5);//sizeM / threadsNum;//p2(5);
            //     blockSizeN = p2(7);
            //     blockSizeK = p2(6);
            // }
            blockSizeM = p2(5);//p2(5);// min p2(3)
            blockSizeN = (blockSizeN < threadsNum * threadsNum) ? 8 : p2(4);//p2(4);// min p2(3)
            blockSizeK = (blockSizeK < threadsNum * threadsNum) ? 8 : p2(7);//p2(5);// min p2(3)
            threadsCols = 1;
            threadsRows = sizeM / blockSizeM;
            if (blockSizeM * threadsRows != sizeM)
                exit(0);
            // printf("%d | %d | %d\n", blockSizeM, blockSizeN, blockSizeK);
            // printf("size %d | %d | %d\n", sizeM, sizeN, sizeK);
            // if (sizeM % 32 != 0 || sizeK % 16 != 0 || sizeK < 32 || sizeM < 16)
            //     exit(0);
            if (sizeM % 64 != 0 || sizeK % 16 != 0 || sizeK < 64 || sizeM < 16)
                exit(0);
            //clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            omp_start = omp_get_wtime();
            for (int i = 0; i < N; i++)
                AsmMatrixMulParallelV6(in At, in B, out C, sizeM, sizeN, sizeK, blockSizeM, blockSizeN, blockSizeK, threadsNum, threadsCols, threadsRows);
            omp_end = omp_get_wtime();
            time_in_seconds = abs(omp_end - omp_start) / static_cast<double>(N);
            // clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            // timeC = diff(start, end);
            // time_in_seconds = (static_cast<double>(timeC.tv_sec) + static_cast<double>(timeC.tv_nsec) / 1.0e9) / static_cast<double>(N);
            //printf("%f sec\n", time_in_seconds);
            tacts = time_in_seconds * curProcessor.clock;
            tacts_theoretical = sizeM * sizeN * sizeK / 16;
            performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
            // printf("%d tacts\n", tacts);
            // printf("%d tacts theoretical\n", tacts_theoretical);
            // printf("%f %% performance\n\n", performance * 100);
            printf("%f\n", performance * 100);
            //MatrixPrint(C, sizeM * sizeK, sizeK);
            break;
        default:
            printf("Function name is incorrect!\n\n");
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
    }
    delete[] At;
    return 0;
}