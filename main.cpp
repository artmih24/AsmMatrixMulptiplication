#include <malloc.h>
#include <string.h>
#include <math.h>
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
    } 
    else if (argc <= 2) {
        file = fopen(argc == 1 ? "input8.txt" : argv[1], "r");
        if (!fscanf(file, "%d", &sizeM))
            printf("Can't read file\n");
        else if (!fscanf(file, "%d", &sizeN))
            printf("Can't read file\n");
        else if (!fscanf(file, "%d", &sizeK))
            printf("Can't read file\n");
    }
    int blockSize_min = 8,
        blockSizeMmax = p2(7),//p2(9),//p2(7),//7
        blockSizeNmax = p2(5),//p2(6),//p2(5),//5
        blockSizeKmax = p2(9),//p2(10),//p2(9),//9
        blockSizeM = (sizeM < blockSizeMmax) ? sizeM : (blockSizeMmax > blockSize_min) ? blockSizeMmax : blockSize_min,
        blockSizeN = (sizeN < blockSizeNmax) ? sizeN : (blockSizeNmax > blockSize_min) ? blockSizeNmax : blockSize_min,
        blockSizeK = (sizeK < blockSizeKmax) ? sizeK : (blockSizeKmax > blockSize_min) ? blockSizeKmax : blockSize_min,
        threadsNum = 8;//sizeM / blockSizeM; 
    //threadsNum = threadsNum > 8 ? 8 : threadsNum;
    //printf("%d | %d | %d\n", blockSizeM, blockSizeN, blockSizeK);
    // if (blockSizeM % 32 != 0) 
    //     blockSizeM = (ceil(blockSizeM / 32) + 1) * 32;
    // if (blockSizeK % 16 != 0) 
    //     blockSizeK = (ceil(blockSizeK / 32) + 1) * 32;
    //printf("%d | %d | %d\n", blockSizeM, blockSizeN, blockSizeK);
    if (sizeN % blockSizeN != 0) 
        sizeN += sizeN - sizeN % blockSizeN;
    if (sizeM % blockSizeM != 0) 
        sizeM += sizeM - sizeM % blockSizeM;
    if (sizeK % blockSizeK != 0) 
        sizeK += sizeK - sizeK % blockSizeK;
    //printf("size %d | %d | %d\n", sizeM, sizeN, sizeK);
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
    char argRandomDiff[] = "--random_diff",
        argRD[] = "--RD",
        argIncrementDiff[] = "--increment_diff",
        argID[] = "--ID",
        argRandomMatrix[] = "--random_matrix",
        argRM[] = "--RM",
        argIncrementMatrix[] = "--increment_matrix",
        argIM[] = "--IM",
        argRandomDiffMatrix[] = "--random_diff_matrix",
        argRDM[] = "--RDM",
        argIncrementDiffMatrix[] = "--increment_diff_matrix",
        argIDM[] = "--IDM";
    if (argc == 5) {
        char argRandom[] = "--random",
            argR[] = "--R",
            argIncrement[] = "--increment",
            argI[] = "--I";
        if (compare(argv[1], argRandom) || 
            compare(argv[1], argR) ||
            compare(argv[1], argRandomDiff) || 
            compare(argv[1], argRD) ||
            compare(argv[1], argRandomMatrix) || 
            compare(argv[1], argRM) ||
            compare(argv[1], argRandomDiffMatrix) || 
            compare(argv[1], argRDM)) {
            srand(time(0)); 
            MatrixInitByRnd(out A, sizeA);
            MatrixInitByRnd(out B, sizeB);
        }
        else if (compare(argv[1], argIncrement) || 
                 compare(argv[1], argI) ||
                 compare(argv[1], argIncrementDiff) || 
                 compare(argv[1], argID) ||
                 compare(argv[1], argIncrementMatrix) || 
                 compare(argv[1], argIM) ||
                 compare(argv[1], argIncrementDiffMatrix) || 
                 compare(argv[1], argIDM)) {
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

    if (compare(argv[1], argIncrementDiff) || 
        compare(argv[1], argID) ||
        compare(argv[1], argRandomDiff) || 
        compare(argv[1], argRD) ||
        compare(argv[1], argIncrementDiffMatrix) || 
        compare(argv[1], argIDM) ||
        compare(argv[1], argRandomDiffMatrix) || 
        compare(argv[1], argRDM))
        MatrixMulTime(FuncMatrixMul1, in A, in B, out C, sizeM, sizeN, sizeK, blockSizeM, blockSizeN, blockSizeK, threadsNum, 1);

    //MatrixMulTime(FuncMatrixMul1, in A, in B, out C, sizeM, sizeN, sizeK, blockSizeM, blockSizeN, blockSizeK, threadsNum, 1);
    MatrixMulTime(FuncAsmMatrixMulParallelV6N, in A, in B, out C2, sizeM, sizeN, sizeK, blockSizeM, blockSizeN, blockSizeK, threadsNum, 1);
    //MatrixMulTime(FuncAsmMatrixMulBlockV6N, in A, in B, out C2, sizeM, sizeN, sizeK, blockSizeM, blockSizeN, blockSizeK, threadsNum, 1);
    //MatrixMulTime(FuncAsmMatrixMulV6N, in A, in B, out C2, sizeM, sizeN, sizeK, blockSizeM, blockSizeN, blockSizeK, threadsNum, 1);
    
    // MatrixPrintV2(C, sizeC, sizeK);
    // MatrixPrintV2(C2, sizeC, sizeK);

    if (compare(argv[1], argRandomMatrix) ||
        compare(argv[1], argRM) ||
        compare(argv[1], argRandomDiffMatrix) ||
        compare(argv[1], argRDM) ||
        compare(argv[1], argIncrementMatrix) ||
        compare(argv[1], argIM) ||
        compare(argv[1], argIncrementDiffMatrix) ||
        compare(argv[1], argIDM))
        MatrixPrintV2(C2, sizeC, sizeK);

    if (compare(argv[1], argIncrementDiff) || 
        compare(argv[1], argID) ||
        compare(argv[1], argRandomDiff) || 
        compare(argv[1], argRD) ||
        compare(argv[1], argIncrementDiffMatrix) || 
        compare(argv[1], argIDM) ||
        compare(argv[1], argRandomDiffMatrix) || 
        compare(argv[1], argRDM))
        PrintDiff(C, C2, sizeM * sizeK, sizeK);

    delete[] A, B, C, C2, At;
    return 0;
}