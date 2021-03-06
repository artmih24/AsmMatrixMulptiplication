#ifndef MATRIXMULFUNCTIONS_H
#define MATRIXMULFUNCTIONS_H

int AsmMatrixMul(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int AsmMatrixMulV2(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int AsmMatrixMulV3(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int AsmMatrixMulV4(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int AsmMatrixMulV5(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int AsmMatrixMulBlockV5(float *A, float *B, float *C, int sizeM, int sizeN, int sizeK);

int AsmMatrixMulV6(float *At, float *B, float *C, int sizeM, int sizeN, int sizeK);

int AsmMatrixMulBlockMKV6(float *At, float *B, float *C, int sizeM, int sizeN, int sizeK);

int AsmMatrixMulBlockV6(float *At, float *B, float *C, int sizeM, int sizeN, int sizeK, int blockSizeM, int blockSizeN, int blockSizeK);

int AsmMatrixMulParallelV6_old(float *At, 
                               float *B, 
                               float *C, 
                               int sizeM, 
                               int sizeN, 
                               int sizeK, 
                               int blockSizeM, 
                               int blockSizeN, 
                               int blockSizeK, 
                               int threadsNum, 
                               int threadsCols, 
                               int threadsRows);

int AsmMatrixMulParallelV6_8(float *At, 
                             float *B, 
                             float *C, 
                             int sizeM, 
                             int sizeN, 
                             int sizeK, 
                             int blockSizeM, 
                             int blockSizeN, 
                             int blockSizeK, 
                             int threadsNum, 
                             int threadsCols, 
                             int threadsRows);

int AsmMatrixMulParallelV6_25_04(float *At, 
                                 float *B, 
                                 float *C, 
                                 int sizeM, 
                                 int sizeN, 
                                 int sizeK, 
                                 int blockSizeM, 
                                 int blockSizeN, 
                                 int blockSizeK, 
                                 int threadsNum, 
                                 int threadsCols, 
                                 int threadsRows);

int AsmMatrixMulParallelV6(float *At, 
                           float *B, 
                           float *C, 
                           int sizeM, 
                           int sizeN, 
                           int sizeK, 
                           int blockSizeM, 
                           int blockSizeN, 
                           int blockSizeK, 
                           int threadsNum, 
                           int threadsCols, 
                           int threadsRows);

#endif