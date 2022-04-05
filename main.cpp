#include <malloc.h>
#include <string.h>
#include "functions.h"
#include "MatrixMulSwitch.h"

int main(int argc, char* argv[]) {
    int sizeM = 0, // Q
        sizeN = 0, // L
        sizeK = 0, // F
        sizeA = 0, // Q*L
        sizeB = 0, // L*F
        sizeC = 0, // Q*F
        i = 0,
        j = 0;
    FILE *file;
    if (argc == 5) {
        sizeM = atoi(argv[2]);
        sizeN = atoi(argv[3]);
        sizeK = atoi(argv[4]);
    } else if (argc <= 2) {
        file = fopen(argc == 1 ? "input8.txt" : argv[1], "r");
        if (!fscanf(file, "%d", &sizeM))
            printf("Can't read file\n");
        else if (!fscanf(file, "%d", &sizeN))
            printf("Can't read file\n");
        else if (!fscanf(file, "%d", &sizeK))
            printf("Can't read file\n");
    }
    //printf("[%dx%d] * [%dx%d] => [%dx%d]\n\n", sizeM, sizeN, sizeN, sizeK, sizeM, sizeK);
    sizeA = sizeM * sizeN;
    sizeB = sizeN * sizeK;
    sizeC = sizeM * sizeK;
    float *A = new float[sizeA],
        *B = new float[sizeB],
        *C = new float[sizeC],
        *C2 = new float[sizeC],
        *At = new float[sizeA];
    MatrixInitBy0(A, sizeA);
    MatrixInitBy0(B, sizeB);
    MatrixInitBy0(C, sizeC);
    MatrixInitBy0(C2, sizeC);
    MatrixInitBy0(At, sizeA);
    if (argc == 5) {
        char argRandom[] = "--random",
            argR[] = "--R",
            argIncrement[] = "--increment",
            argI[] = "--I";
        if (compare(argv[1], argRandom) || compare(argv[1], argR)) {
            srand(time(0)); 
            MatrixInitByRnd(out A, sizeA);
            MatrixInitByRnd(out B, sizeB);
        }
        else if (compare(argv[1], argIncrement) || compare(argv[1], argI)) {
            MatrixInitByIncrement(out A, sizeM, sizeN);
            MatrixInitByIncrement(out B, sizeN, sizeK, 5);
        }
        else {
            printf("Wrong option!\n");
            return -1;
        }
    } else {
        MatrixReadFromFile(out A, sizeA, file);
        MatrixReadFromFile(out B, sizeB, file);
        fclose(file);
    }
    //MatrixPrintV2(A, sizeA, sizeN);
    //MatrixPrintV2(B, sizeB, sizeK);

    //MatrixTranspose(in A, out At, sizeM, sizeN);
    //MatrixPrintV2(At, sizeA, sizeM);

    //MatrixMulTime(FuncMatrixMul1, in A, in B, out C, sizeM, sizeN, sizeK, 1);
    MatrixMulTime(FuncAsmMatrixMulBlockV6N, in A, in B, out C2, sizeM, sizeN, sizeK, 1);
    //MatrixMulTime(FuncAsmMatrixMulV6N, in A, in B, out C2, sizeM, sizeN, sizeK, 9);

    //MatrixPrintV2(C, sizeC, sizeK);
    //MatrixPrintV2(C2, sizeC, sizeK);

    //PrintDiff(C, C2, sizeM * sizeK, sizeK);

    delete[] A, B, C, C2, At;
    return 0;
}