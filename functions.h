#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "asmfunctions.h"

#define i7_4790K_Hz 4e9

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
    FuncAsmMatrixMulV4N
};

timespec diff(timespec start, timespec end);

int MatrixMulTime(int func, float *A, float *B, float *C, int sizeM, int sizeN, int sizeK, int N = 1);

int MatrixMul(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int MatrixMul1(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int MatrixMulTest(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int AsmMatrixMul(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int AsmMatrixMulV2(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int AsmMatrixMulV3(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int AsmMatrixMulV4(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int MatrixInitBy0(float *M, int sizeM);

int MatrixInitByIncrement(float *M, int rows, int cols, int start = 0, int step = 1);

int MatrixInitByRnd(float *M, int sizeM);

int MatrixReadFromFile(float *M, int sizeM, FILE *file);

int MatrixPrint(float *M, int sizeM, int sizeL);

float MaxDiff(float *C, float *C2, int size, int len);

float AvgDiff(float *C, float *C2, int size);

float RelMaxDiff(float *C, float *C2, int size);

float RelAvgDiff(float *C, float *C2, int size);

int is_cmp(const char* s1, const char* s2);

int compare(const char* s1, const char* s2);

#endif