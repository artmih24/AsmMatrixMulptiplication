#include "functions.h"
#include "MatrixMulFunctions.h"
#include "MatrixMulSwitch.h"

int MatrixMulTime(int func, float *A, float *B, float *C, int sizeM, int sizeN, int sizeK, int blockSizeM, int blockSizeN, int blockSizeK, int N) {
    timespec start, end, timeC;
    double time_in_seconds = 0.0;
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
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            AsmMatrixMulParallelV6(in At, in B, out C, sizeM, sizeN, sizeK, blockSizeM, blockSizeN, blockSizeK);
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
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMulParallelV6(in At, in B, out C, sizeM, sizeN, sizeK, blockSizeM, blockSizeN, blockSizeK);
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
        default:
            printf("Function name is incorrect!\n\n");
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
    }
    delete[] At;
    return 0;
}