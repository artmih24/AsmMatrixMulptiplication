#include "MatrixMulFunctions.h"
#include "asmfunctions.h"
#include "functions.h"
#include <stdlib.h>
#include <math.h>


int AsmMatrixMulBlockV5(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK) {
    int i = 0,
        j = 0,
        k = 0,
        l = 0,
        m = 0,
        blockSizeM = (sizeM < 16) ? sizeM : 16,
        blockSizeK = (sizeK < 16) ? sizeK : 16,
        offsetM = 0,
        offsetK = 0,
        offsetI = 0,
        offsetJ = 0;      
    float *fragA = 0,
        *fragB = 0,
        *fragC = 0;
    timespec start, end, timeC;
    for (m = 0; m < sizeM / blockSizeM; m++) {
        offsetM = m * blockSizeM * sizeK;
        for (k = 0; k < sizeK / blockSizeK; k++) {
            offsetK = k * blockSizeK;
            for (i = 0; i < blockSizeM / 8; i++) {
                offsetI = 8 * i * sizeM / blockSizeM;
                fragA = A + offsetI + offsetM;
                for (j = 0; j < blockSizeK / 8; j++) {
                    offsetJ = 8 * j;
                    fragB = B + offsetJ + offsetK;
                    fragC = C + offsetI + offsetJ + offsetK + offsetM;
                    // clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
                    // for (int k = 0; k < 1e9; k++)
                    AsmPartSumV5(fragA, fragB, fragC, sizeN, blockSizeK);
                    // clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
                    // timeC = diff(start, end);
                    // double time_in_seconds = (timeC.tv_sec + timeC.tv_nsec / 1.0e9) / 1.0e9;
                    // printf("%f sec\n", time_in_seconds);
                    // u_int64_t tacts = time_in_seconds * i5_9600KF_Hz,
                    //     tacts_theoretical = sizeN;
                    // float performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
                    // printf("%f\n", performance * 100);
                }
            }
        }
    }
    return 0;
}

int AsmMatrixMulV5(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK) {
    int i = 0,
        j = 0,
        k = 0;
    float *fragA = 0,
        *fragB = 0,
        *fragC = 0;
    timespec start, end;
    for (i = 0; i < sizeM / 8; i++) {
        fragA = A + 8 * i * sizeN;
        for (j = 0; j < sizeK / 8; j++) {
            fragB = B + 8 * j;
            fragC = C + 8 * i * sizeK + 8 * j;
            // clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            // for (int k = 0; k < 1e9; k++)
            AsmPartSumV5(fragA, fragB, fragC, sizeN, sizeK);
            // clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            // timespec timeC = diff(start, end);
            // double time_in_seconds = (timeC.tv_sec + timeC.tv_nsec / 1.0e9) / 1.0e9;
            // printf("%f sec\n", time_in_seconds);
            // u_int64_t tacts = time_in_seconds * i5_9600KF_Hz,
            //     tacts_theoretical = sizeN;
            // float performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
            // printf("%f\n", performance * 100);
        }
    }
    return 0;
}

int AsmMatrixMulV4(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK) {
    int i = 0,
        j = 0,
        k = 0,
        flag = 0;
    float *fragA = 0,
        *fragB = 0,
        *fragC = 0;
    timespec start, end;
    for (i = 0; i < sizeM / 4; i++) {
        fragA = A + 4 * i * sizeN;
        for (j = 0; j < ceil(sizeK / 16); j++) {
            fragB = B + 16 * j;
            fragC = C + 4 * i * sizeK + 16 * j;
            flag = (j < ceil(sizeK / 16) - 1) ? 0 : sizeK % 16;
            // clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            // for (int k = 0; k < 1e9; k++)
            AsmPartSumV4(fragA, fragB, fragC, sizeN, sizeK, flag);
            // clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            // timespec timeC = diff(start, end);
            // double time_in_seconds = (timeC.tv_sec + timeC.tv_nsec / 1.0e9) / 1.0e9;
            // printf("%f sec\n", time_in_seconds);
            // u_int64_t tacts = time_in_seconds * i5_9600KF_Hz,
            //     tacts_theoretical = sizeN;
            // float performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
            // printf("%f\n", performance * 100);
        }
    }
    return 0;
}

int AsmMatrixMulV3(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK) {
    int i = 0,
        j = 0,
        k = 0;
    float *fragA = 0,
        *fragB = 0,
        *fragC = 0;
    timespec start, end;
    for (i = 0; i < sizeM / 4; i++) {
        fragA = A + 4 * i * sizeN;
        for (j = 0; j < sizeK / 16; j++) {
            fragB = B + 16 * j;
            fragC = C + 4 * i * sizeK + 16 * j;
            //clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            // unsigned int start = clock();
            // for (int k = 0; k < 1e6; k++)
            AsmPartSumV3(fragA, fragB, fragC, sizeN, sizeK);
            // unsigned int end = clock();
            // unsigned int search_time = end - start;
            // //clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            // //timespec timeC = diff(start, end);
            // double time_in_seconds = 1.0 * search_time / CLOCKS_PER_SEC;//(timeC.tv_sec + timeC.tv_nsec / 1.0e9);// / 1.0e9;
            // printf("%f sec\n", time_in_seconds);
            // u_int64_t tacts = time_in_seconds * i5_9600KF_Hz,
            //     tacts_theoretical = sizeN * 4 * 1e6;
            // //printf("%d %d\n", tacts, tacts_theoretical);
            // double performance = static_cast<double>(tacts_theoretical) / static_cast<double>(tacts);
            // printf("%f\n", performance * 100);
        }
    }
    return 0;
}

int AsmMatrixMulV2(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK) {
    int i = 0,
        j = 0,
        k = 0;
    float *fragA = 0,
        *fragB = 0,
        *fragC = 0;
    timespec start, end;
    for (i = 0; i < sizeM / 4; i++) {
        fragA = A + 4 * i * sizeN;
        for (j = 0; j < sizeK / 8; j++) {
            fragB = B + 8 * j;
            fragC = C + 4 * i * sizeK + 8 * j;
            // clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            // for (int k = 0; k < 1e9; k++)
            AsmPartSumV2(fragA, fragB, fragC, sizeN, sizeK);
            // clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            // timespec timeC = diff(start, end);
            // double time_in_seconds = (timeC.tv_sec + timeC.tv_nsec / 1.0e9) / 1.0e9;
            // printf("%f sec\n", time_in_seconds);
            // u_int64_t tacts = time_in_seconds * i5_9600KF_Hz,
            //     tacts_theoretical = sizeN;
            // float performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
            // printf("%f\n", performance * 100);
        }
    }
    return 0;
}

int AsmMatrixMul(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK) {
    int i = 0,
        j = 0,
        k = 0;
    float *fragA = 0,
        *fragB = 0,
        *fragC = 0;
    timespec start, end;
    for (i = 0; i < sizeM; i++) {
        fragA = A + i * sizeN;
        for (j = 0; j < sizeK / 8; j++) {
            fragB = B + 8 * j;
            fragC = C + i * sizeK + 8 * j;
            // clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            // for (int k = 0; k < 1e9; k++)
            AsmPartSum(fragA, fragB, fragC, sizeN, sizeK);
            // clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            // timespec timeC = diff(start, end);
            // double time_in_seconds = (timeC.tv_sec + timeC.tv_nsec / 1.0e9) / 1.0e9;
            // printf("%f sec\n", time_in_seconds);
            // u_int64_t tacts = time_in_seconds * i5_9600KF_Hz,
            //     tacts_theoretical = sizeN;
            // float performance = static_cast<float>(tacts_theoretical) / static_cast<float>(tacts);
            // printf("%f\n", performance * 100);
        }
    }
    return 0;
}