#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include <ctime>

#include "asmfunctions.h"

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

int MatrixMulTime(int func, float *A, float *B, float *C, int sizeM, int sizeN, int sizeK, int N) {
    timespec start, end, timeC;
    double time_in_seconds = 0.0;
    u_int64_t tacts = 0,
        tacts_theoretical = 0;
    float performance = 0.0;
    Processor i7_4790K;
    i7_4790K.clock = 4e9;
    i7_4790K.clockBoost = 4.4e9;
    i7_4790K.sizeCacheL1 = 1.024e6;
    i7_4790K.sizeCacheL2 = 8e6;
    i7_4790K.sizeCacheL3 = 6.4e7;
    Processor i5_9600KF;
    i5_9600KF.clock = 3.7e9;
    i5_9600KF.clockBoost = 4.6e9;
    i5_9600KF.sizeCacheL1 = 1.536e6;
    i5_9600KF.sizeCacheL2 = 1.2e7;
    i5_9600KF.sizeCacheL3 = 7.2e7;
    Processor curProcessor = i5_9600KF;
    switch (func) {
        case (FuncMatrixMul):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            MatrixMul(A, B, C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncMatrixMul1):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            MatrixMul1(A, B, C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncMatrixMulTest):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            MatrixMulTest(A, B, C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMul):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            AsmMatrixMul(A, B, C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulN):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMul(A, B, C, sizeM, sizeN, sizeK);
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
            AsmMatrixMulV2(A, B, C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulV2N):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMulV2(A, B, C, sizeM, sizeN, sizeK);
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
            AsmMatrixMulV3(A, B, C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulV3N):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMulV3(A, B, C, sizeM, sizeN, sizeK);
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
            AsmMatrixMulV4(A, B, C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulV4N):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMulV4(A, B, C, sizeM, sizeN, sizeK);
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
            AsmMatrixMulV5(A, B, C, sizeM, sizeN, sizeK);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            break;
        case (FuncAsmMatrixMulV5N):
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
            for (int i = 0; i < N; i++)
                AsmMatrixMulV5(A, B, C, sizeM, sizeN, sizeK);
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
    return 0;
}

timespec diff(timespec start, timespec end) {
    timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + (end.tv_nsec - start.tv_nsec);
        //printf("neg tv_sec = %ld, tv_nsec = %ld\n\n", temp.tv_sec, temp.tv_nsec);
    }
    else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
        //printf("tv_sec = %ld, tv_nsec = %ld\n\n", temp.tv_sec, temp.tv_nsec);
    }
    return temp;
}

int MatrixMul(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK) {
    int i = 0,
        j = 0,
        k = 0;
    for (i = 0; i < sizeM; i++) {
        int iK = i * sizeK,
            iN = i * sizeN;
        for (k = 0; k < sizeK; k++) {
            int iKk = iK + k;
            C[iKk] = 0.0;
            for (j = 0; j < sizeN; j++)
                C[iKk] += A[iN + j] * B[j * sizeK + k];
        }
    }
    return 0;
}

int MatrixMul1(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK) {
    int i = 0,
        j = 0,
        k = 0;
    for (i = 0; i < sizeM; i++)
        for (k = 0; k < sizeK; k++)
            C[i * sizeK + k] = 0.0;
    for (i = 0; i < sizeM; i++)
        for (j = 0; j < sizeN; j++)
            for (k = 0; k < sizeK; k++)
                C[i * sizeK + k] += A[i * sizeN + j] * B[j * sizeK + k];
    return 0;
}

int MatrixMulTest(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK) {
    int i = 0,
        j = 0,
        k = 0;
    for (i = 0; i < sizeM; i++)
        for (k = 0; k < sizeK; k++)
            C[i * sizeK + k] = 0.0;
    for (i = 0; i < sizeM; i++)
        for (j = 0; j < sizeN; j++)
            for (k = 0; k < sizeK; k++)
                C[i * sizeK + k] += A[i * sizeN + j] * B[j * sizeK + k];
    return 0;
}

int MatrixInitByIncrement(float *M, int rows, int cols, int start, int step) {
    int i = 0,
        j = 0;
    for (i = 0; i < cols; i++)
        for (j = 0; j < rows; j++){
            M[i * rows + j] = (i + step) * (j + step) + start;
            while (M[i * rows + j] > 10) {
                M[i * rows + j] /= 10.0;
            }
        }
    return 0;
}

int MatrixInitBy0(float *M, int sizeM) {
    int i = 0;
    for (i = 0; i < sizeM; i++)
        M[i] = 0.0;
    return 0;
}

int MatrixInitByRnd(float *M, int sizeM) {
    int i = 0;
    for (i = 0; i < sizeM; i++)
        M[i] = (float)(rand() % (20 * 256));// / 256.0;
    return 0;
}

int MatrixReadFromFile(float *M, int sizeM, FILE *file) {
    int i = 0;
    for (i = 0; i < sizeM; i++)
        if (!fscanf(file, "%f", &M[i])){
            printf("Can't read file\n");
            break;
        }
    return 0;
}

int MatrixPrint(float *M, int sizeM, int sizeL) {
    int i = 0;
    for (i = 0; i < sizeM; i++) {
        printf("%.3f ", M[i]);
        //printf("%.4f\t", M[i]);
        if (i % sizeL == sizeL - 1)
            printf("\n");
        if (i == sizeM - 1)
            printf("\n");
    }
    return 0;
}

float MaxDiff(float *C, float *C2, int size, int len) {
    int i = 0;
    float maxDiff = 0.0,
        diff = 0;
    for (i = 0; i < size; i++) {
        diff = abs(C[i] - C2[i]);
        // if (diff > 0)
        //     printf("|%f - %f| = %f\n", C[i], C2[i], diff);
        //     printf("|%f - %f|[%d, %d] = %f\n", C[i], C2[i], i % len, (int) i / len, diff);
        if (diff > maxDiff)
            maxDiff = diff;
    }
    return maxDiff;
}

float AvgDiff(float *C, float *C2, int size) {
    int i = 0;
    float sumDiff = 0.0;
    for (i = 0; i < size; i++)
        sumDiff += abs(C[i] - C2[i]);
    return sumDiff / size;
}

float RelMaxDiff(float *C, float *C2, int size) {
    int i = 0;
    float maxDiff = 0.0,
        diff = 0;
    for (i = 0; i < size; i++) {
        diff = abs(C[i] - C2[i]) / C[i];
        // if (diff > 0)
        //     printf("|%f - %f| = %f\n", C[i], C2[i], diff);
        if (diff > maxDiff)
            maxDiff = diff;
    }
    return maxDiff;
}

float RelAvgDiff(float *C, float *C2, int size) {
    int i = 0;
    float sumDiff = 0.0;
    for (i = 0; i < size; i++) 
        sumDiff += abs(C[i] - C2[i]) / C[i];
    return sumDiff / size;
}

int PrintDiff(float *C, float *C2, int size, int len) {
    printf("\u0394 max = %f\n", MaxDiff(C, C2, size, len));
    printf("\u0394 avg = %f\n", AvgDiff(C, C2, size));
    printf("\u03B4 max = %f\n", RelMaxDiff(C, C2, size));
    printf("\u03B4 avg = %f\n", RelAvgDiff(C, C2, size));
    return 0;
}

int is_cmp(const char* s1, const char* s2) {
    int m = 0;
    const unsigned char* p;
    short abc[256]; 
    memset(abc, 0, sizeof(abc));
    for (p = (const unsigned char*)s1; *p; ++p, ++m)
        ++abc[*p];
    for (p = (const unsigned char*)s2; *p; ++p, --m)
        if (--abc[*p] < 0) 
            return 0;
    return (m == 0);
}

int compare(const char* s1, const char* s2) {
    const char *p1 = s1, 
        *p2 = s2;
    for (; *p1||*p2; p1++, p2++) 
        if (*p1 != *p2) 
            return false;
    return !(*p1 || *p2);
}