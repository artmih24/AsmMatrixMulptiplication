#ifndef ASMFUNCTIONS_H
#define ASMFUNCTIONS_H

extern "C" float* AsmPartSum(float *fragA, float *fragB, float *fragC, int sizeN, int sizeK);

extern "C" float* AsmPartSumV2(float *fragA, float *fragB, float *fragC, int sizeN, int sizeK);

extern "C" float* AsmPartSumV3(float *fragA, float *fragB, float *fragC, int sizeN, int sizeK);

extern "C" float* AsmPartSumV4(float *fragA, float *fragB, float *fragC, int sizeN, int sizeK, int flag);

#endif