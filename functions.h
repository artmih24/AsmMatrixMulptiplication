#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "asmfunctions.h"

#define i7_4790K_Hz 4e9
#define i7_4790K_Hz_Boost 4.4e9
#define i5_9600KF_Hz 3.7e9

#define p2(x) 1 << x
#define p8(x) 1 << (3 * x)

struct Processor {
    u_int64_t clock;
    u_int64_t clockBoost;
    u_int64_t sizeCacheL1;
    u_int64_t sizeCacheL2;
    u_int64_t sizeCacheL3;
};

enum FuncsMatrMul {
    FuncMatrixMul,
    FuncMatrixMul1,
    FuncMatrixMulTest,
    FuncAsmMatrixMul,
    FuncAsmMatrixMulN,
    FuncAsmMatrixMulV2,
    FuncAsmMatrixMulV2N,
    FuncAsmMatrixMulV3,
    FuncAsmMatrixMulV3N,
    FuncAsmMatrixMulV4,
    FuncAsmMatrixMulV4N,
    FuncAsmMatrixMulV5,
    FuncAsmMatrixMulV5N,
    FuncAsmMatrixMulBlockV5,
    FuncAsmMatrixMulBlockV5N,
    FuncAsmMatrixMulV6,
    FuncAsmMatrixMulV6N,
    FuncAsmMatrixMulBlockV6,
    FuncAsmMatrixMulBlockV6N,
    FuncAsmMatrixMulParallelV6,
    FuncAsmMatrixMulParallelV6N
};

timespec diff(timespec start, timespec end);

int MatrixTranspose(float *M, float *Mt, int lines, int cols);

int MatrixMul(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int MatrixMul1(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int MatrixMulTest(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int MatrixInitBy0(float *M, int sizeM);

int MatrixInitBy0(int *M, int sizeM);

int MatrixInitByIncrement(float *M, int rows, int cols, int start = 0, int step = 1);

int MatrixInitByRnd(float *M, int sizeM);

int MatrixReadFromFile(float *M, int sizeM, FILE *file);

int MatrixPrint(float *M, int sizeM, int sizeL);

int MatrixPrintV2(float *M, int sizeM, int sizeL);

int MatrixPrintV3(float *M, int sizeM, int sizeL);

float MaxDiff(float *C, float *C2, int size, int len);

float AvgDiff(float *C, float *C2, int size);

float RelMaxDiff(float *C, float *C2, int size);

float RelAvgDiff(float *C, float *C2, int size);

int PrintDiff(float *C, float *C2, int size, int len);

int is_cmp(const char* s1, const char* s2);

int compare(const char* s1, const char* s2);

#endif