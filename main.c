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
    char **stringsPointer = alocArrayList(listSize);

    for (int i = 0; i < listSize; i++) {
        convertToString(i, atoi(argv[i+1]), &stringsPointer);
    }

    for (int i = 0; i < listSize; i++) {
        printf("\nBinary representation of %d: %s\n", atoi(argv[i+1]), &stringsPointer[i][1]);
        int onesCount = stringsPointer[i][0] - '0'; // Convert character back to integer
        printf("Number of ones in binary representation: %d\n", onesCount);
    }

    int mintermGroups[NUMBER_OF_BITS + 1];  // Array to store counts of ones for each group
    for (int group = 0; group <= NUMBER_OF_BITS; group++) {
        mintermGroups[group] = 0;
    }

    int lastIndexGroups[listSize];
    for (int i = 0; i < listSize; i++) {
        lastIndexGroups[i] = 0;
    }

    char*** primesGroups = groupByOnes(stringsPointer, listSize, mintermGroups, lastIndexGroups);

    printPrimesGroups(lastIndexGroups, primesGroups);
    groupMinterms(lastIndexGroups, primesGroups);
    printPrimesGroups(lastIndexGroups, primesGroups);
    // // Print the grouped binary strings for each group
    // for (int i = 0; i <= NUMBER_OF_BITS; i++) {  // Include the group for zero ones
    //     printf("Group %d (Count of Ones: %d):\n", i, i);
    //     for (int j = 0; j < mintermGroups[i]; j++) {
    //         printf("%s\n", primesGroups[i][j]);
    //     }
    // }

    // groupMinterms(stringsPointer);

    // printf("\n---------------Grouped Minterms---------------\n");
    
    // for (int i = 0; i < NUMBER_OF_BITS - 1; i++) {
    //     printf("Group %d (Count of Ones: %d):\n", i, i);
    //     printf("%s\n", stringsPointer[i]);
    // }

    freeMemoryGroups(primesGroups, mintermGroups, NUMBER_OF_BITS + 1);  // Include the group for zero ones
    freeMemory(stringsPointer, NULL, 0);
    return 0;
}