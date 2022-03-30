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
        *C3 = new float[sizeC],
        *C4 = new float[sizeC],
        *C5 = new float[sizeC],
        *C6 = new float[sizeC],
        *C7 = new float[sizeC],
        *C8 = new float[sizeC],
        *C9 = new float[sizeC],
        *At = new float[sizeA];
    MatrixInitBy0(A, sizeA);
    MatrixInitBy0(B, sizeB);
    MatrixInitBy0(C, sizeC);
    MatrixInitBy0(C2, sizeC);
    MatrixInitBy0(C3, sizeC);
    MatrixInitBy0(C4, sizeC);
    MatrixInitBy0(C5, sizeC);
    MatrixInitBy0(C6, sizeC);
    MatrixInitBy0(C7, sizeC);
    MatrixInitBy0(C8, sizeC);
    MatrixInitBy0(C9, sizeC);
    MatrixInitBy0(At, sizeA);
    if (argc == 5) {
        char argRandom[] = "--random",
            argR[] = "--R",
            argIncrement[] = "--increment",
            argI[] = "--I";
        if (compare(argv[1], argRandom) || compare(argv[1], argR)) {
            srand(time(0)); 
            MatrixInitByRnd(A, sizeA);
            MatrixInitByRnd(B, sizeB);
        }
        else if (compare(argv[1], argIncrement) || compare(argv[1], argI)) {
            MatrixInitByIncrement(A, sizeM, sizeN);
            MatrixInitByIncrement(B, sizeN, sizeK, 5);
        }
        else {
            printf("Wrong option!\n");
            return -1;
        }
    } else {
        MatrixReadFromFile(A, sizeA, file);
        MatrixReadFromFile(B, sizeB, file);
        fclose(file);
    }
    //MatrixPrintV2(A, sizeA, sizeN);
    ////MatrixPrintV2(B, sizeB, sizeK);

    //MatrixTranspose(A, At, sizeM, sizeN);
    //MatrixPrintV2(At, sizeA, sizeM);

    MatrixMulTime(FuncMatrixMul1, A, B, C, sizeM, sizeN, sizeK, 1);
    ////MatrixMulTime(FuncMatrixMul, A, B, C2, sizeM, sizeN, sizeK);
    ////MatrixMulTime(FuncMatrixMulTest, A, B, C3, sizeM, sizeN, sizeK);
    ////MatrixMulTime(FuncAsmMatrixMul, A, B, C4, sizeM, sizeN, sizeK);
    ////MatrixMulTime(FuncAsmMatrixMulV2, A, B, C5, sizeM, sizeN, sizeK);
    ////MatrixMulTime(FuncAsmMatrixMulV3, A, B, C6, sizeM, sizeN, sizeK);
    ////MatrixMulTime(FuncAsmMatrixMulV4, A, B, C7, sizeM, sizeN, sizeK);
    //MatrixMulTime(FuncAsmMatrixMulV6, A, B, C8, sizeM, sizeN, sizeK, 1);
    //MatrixMulTime(FuncAsmMatrixMulBlockV6, A, B, C8, sizeM, sizeN, sizeK);

    ////MatrixMulTime(FuncAsmMatrixMulN, A, B, C4, sizeM, sizeN, sizeK, 9);
    ////MatrixMulTime(FuncAsmMatrixMulV2N, A, B, C5, sizeM, sizeN, sizeK, 9);
    ////MatrixMulTime(FuncAsmMatrixMulV3N, A, B, C6, sizeM, sizeN, sizeK, 9);
    ////MatrixMulTime(FuncAsmMatrixMulV5N, A, B, C8, sizeM, sizeN, sizeK, 9);
    ////MatrixMulTime(FuncAsmMatrixMulBlockV5N, A, B, C8, sizeM, sizeN, sizeK, 9);
    //MatrixMulTime(FuncAsmMatrixMulV6N, A, B, C8, sizeM, sizeN, sizeK, 9);
    MatrixMulTime(FuncAsmMatrixMulBlockV6, A, B, C8, sizeM, sizeN, sizeK, 1);

    MatrixPrintV2(C, sizeC, sizeK);
    //// MatrixPrint(C4, sizeC, sizeK);
    //// MatrixPrint(C5, sizeC, sizeK);
    //// MatrixPrint(C6, sizeC, sizeK);
    //// MatrixPrint(C7, sizeC, sizeK);
    MatrixPrintV2(C8, sizeC, sizeK);

    PrintDiff(C, C8, sizeM * sizeK, sizeK);

    delete[] A, B, C, C2, C3, C4, C5, C6, C7, C8, C9;
    return 0;
}