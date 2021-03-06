#ifndef MATRIXMULSWITCH_H
#define MATRIXMULSWITCH_H

#define in
#define out

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
                  int N = 1);

#endif