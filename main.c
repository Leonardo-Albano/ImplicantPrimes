#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\nArray list needed.");
        return 1;
    }

    int listSize = argc - 1;
    Minterm **mintermsList = allocMintermList(listSize);

    for (int i = 0; i < listSize; i++) {
        convertToString(i, atoi(argv[i+1]), mintermsList);
    }

    for (int i = 0; i < listSize; i++) {
        printf("\nBinary representation of %d: %s\n", mintermsList[i]->originalNumbers[0], mintermsList[i]->binaryRepresentation);
        printf("Number of ones in binary representation: %d\n", mintermsList[i]->countOfOnes);
    }

    int mintermGroups[NUMBER_OF_BITS + 1];  // Array to store counts of ones for each group
    for (int group = 0; group <= NUMBER_OF_BITS; group++) {
        mintermGroups[group] = 0;
    }

    int lastIndexGroups[listSize];
    for (int i = 0; i < listSize; i++) {
        lastIndexGroups[i] = 0;
    }

    Minterm*** primesGroups = groupByOnes(mintermsList, listSize, mintermGroups, lastIndexGroups, 1);
    printPrimesGroups(lastIndexGroups, primesGroups);
    primesGroups = groupMinterms(lastIndexGroups, primesGroups, &listSize);
    printPrimesGroups(lastIndexGroups, primesGroups);

    printf("\nSecond Iteration!!!\n");

    for (int group = 0; group <= NUMBER_OF_BITS; group++) {
        mintermGroups[group] = 0;
    }

    int newLastIndexGroups[listSize];
    for (int i = 0; i < listSize; i++) {
        newLastIndexGroups[i] = 0;
    }
    Minterm** newMintermsList = allocMintermList(listSize);
    newMintermsList = flattenPrimesGroups(primesGroups, lastIndexGroups, newMintermsList);
    
    Minterm*** newPrimesGroups = groupByOnes(newMintermsList, listSize, mintermGroups, newLastIndexGroups, 2);
    printPrimesGroups(newLastIndexGroups, newPrimesGroups);

    // freeMemoryGroups(primesGroups, mintermGroups, NUMBER_OF_BITS + 1);  // Include the group for zero ones
    // freeMemory(mintermsList, NULL, 0);
    freeMintermsList(mintermsList, listSize);
    return 0;
}