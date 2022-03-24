#ifndef ASMFUNCTIONS_H
#define ASMFUNCTIONS_H

// 1x8
extern "C" float* AsmPartSum(float *fragA, float *fragB, float *fragC, int sizeN, int sizeK);

// 4x8
extern "C" float* AsmPartSumV2(float *fragA, float *fragB, float *fragC, int sizeN, int sizeK);

// 4x16
extern "C" float* AsmPartSumV3(float *fragA, float *fragB, float *fragC, int sizeN, int sizeK);

// 4x16 - 4x8
extern "C" float* AsmPartSumV4(float *fragA, float *fragB, float *fragC, int sizeN, int sizeK, int flag);

// 8x8
extern "C" float* AsmPartSumV5(float *fragA, float *fragB, float *fragC, int sizeN, int sizeK);

#endif