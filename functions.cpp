#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include <ctime>

#include "asmfunctions.h"
#include "MatrixMulFunctions.h"


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
        //if (diff > 0)
            ////printf("|%f - %f| = %f\n", C[i], C2[i], diff);
            //printf("|%f - %f|[%d, %d] = %f\n", C[i], C2[i], i % len, (int) i / len, diff);
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