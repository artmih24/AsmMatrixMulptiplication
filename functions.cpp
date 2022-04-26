#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <iostream>

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

int MatrixTranspose(float *M, float *Mt, int lines, int cols) {
    int i = 0,
        j = 0;
    for (i = 0; i < lines; i++) {
        for (j = 0; j < cols; j++) {
            Mt[j * lines + i] = M[i * cols + j];
        }
    }
    return 0;
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

int MatrixInitBy0(int *M, int sizeM) {
    int i = 0;
    for (i = 0; i < sizeM; i++)
        M[i] = 0;
    return 0;
}

int MatrixInitByRnd(float *M, int sizeM) {
    int i = 0;
    for (i = 0; i < sizeM; i++)
        M[i] = (float)(rand() % (20 * 256)) / 256.0;
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
        printf("%.3f", M[i]);
        //printf("%.4f\t", M[i]);
        printf((i % sizeL == sizeL - 1) ? "\n" : " ");
        if (i == sizeM - 1)
            printf("\n");
    }
    return 0;
}

int MatrixPrintV2(float *M, int sizeM, int sizeL) {
    int i = 0,
        maxWidth = 0;
    int *w = new int[sizeM];
    MatrixInitBy0(w, sizeM);
    float curM = 0.0;
    for (i = 0; i < sizeM; i++) {
        curM = M[i];
        while (floor(curM /= 10.0) != 0) {
            maxWidth = (++w[i] > maxWidth) ? w[i] : maxWidth;
        }
    }
    for (i = 0; i < sizeM; i++) {
        while (maxWidth - w[i]++ != 0)
            printf(" ");
        printf("%.3f", M[i]);
        //printf("%.4f\t", M[i]);
        printf((i % sizeL == sizeL - 1) ? "\n" : " ");
        if (i == sizeM - 1)
            printf("\n");
    }
    delete[] w;
    return 0;
}

int MatrixPrintV3(float *M, int sizeM, int sizeL) {
    int i = 0,
        j = 0,
        ind = 0;
    int *w = new int[sizeM],
        *mw = new int[sizeL];
    MatrixInitBy0(w, sizeM);
    MatrixInitBy0(mw, sizeL);
    float curM = 0.0;
    for (i = 0; i < sizeL; i++)
        for (j = 0; j < sizeM / sizeL; j++) {
            ind = i + j * sizeL;
            curM = M[ind];
            while (floor(curM /= 10) != 0)
                mw[i] = (++w[ind] > mw[i]) ? w[ind] : mw[i];
        }
    for (i = 0; i < sizeM; i++) {
        while (mw[i % sizeL] - w[i]++ != 0)
            printf(" ");
        printf("%.3f", M[i]);
        //printf("%.4f\t", M[i]);
        printf((i % sizeL == sizeL - 1) ? "\n" : " ");
        if (i == sizeM - 1)
            printf("\n");
    }
    delete[] w, mw;
    return 0;
}

float MaxDiff(float *C, float *C2, int size, int len) {
    int i = 0;
    float maxDiff = 0.0,
        diff = 0;
    for (i = 0; i < size; i++) {
        diff = abs(C[i] - C2[i]);
        // if (diff > 0)
        //     printf("|%f - %f|[%d][%d] = %f\n", C[i], C2[i], (int) i / len, i % len, diff);
            ////printf("|%f - %f| = %f\n", C[i], C2[i], diff);
        // if (diff > maxDiff)
        //     printf("|%f - %f|[%d][%d] = %f\n", C[i], C2[i], (int) i / len, i % len, diff);
        maxDiff = (diff > maxDiff) ? diff : maxDiff;

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

float MinDiff(float *C, float *C2, int size, int len) {
    int i = 0;
    float minDiff = 999999999999999999999.99,
        diff = 0;
    for (i = 0; i < size; i++) {
        diff = abs(C[i] - C2[i]);
        // if (diff > 0)
        //     printf("|%f - %f|[%d][%d] = %f\n", C[i], C2[i], (int) i / len, i % len, diff);
            ////printf("|%f - %f| = %f\n", C[i], C2[i], diff);
        minDiff = (diff < minDiff) ? diff : minDiff;
    }
    return minDiff;
}

float RelMaxDiff(float *C, float *C2, int size) {
    int i = 0;
    float maxDiff = 0.0,
        diff = 0;
    for (i = 0; i < size; i++) {
        diff = abs(C[i] - C2[i]) / C[i];
        // if (diff > 0)
        //     printf("|%f - %f| = %f\n", C[i], C2[i], diff);
        maxDiff = (diff > maxDiff) ? diff : maxDiff;
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

float RelMinDiff(float *C, float *C2, int size) {
    int i = 0;
    float minDiff = 999999999999999999999.99,
        diff = 0;
    for (i = 0; i < size; i++) {
        diff = abs(C[i] - C2[i]) / C[i];
        // if (diff > 0)
        //     printf("|%f - %f| = %f\n", C[i], C2[i], diff);
        minDiff = (diff < minDiff) ? diff : minDiff;
    }
    return minDiff;
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
    for (; *p1 || *p2; p1++, p2++) 
        if (*p1 != *p2) 
            return false;
    return !(*p1 || *p2);
}