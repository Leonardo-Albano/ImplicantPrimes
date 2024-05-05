#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void groupMinterms(int** stringsPointer) {
    for (int group = 0; group < NUMBER_OF_BITS - 1; group++) {
        int* currentArray = stringsPointer[group];
        int* nextArray = stringsPointer[group + 1];

        // Create a copy of the current array
        int* currentCopy = malloc((currentArray[0] + 1) * sizeof(int));
        memcpy(currentCopy, currentArray, (currentArray[0] + 1) * sizeof(int));

        // Compare the first two numbers in the group to mark differing bits
        int firstNum = currentArray[1];
        int secondNum = currentArray[2];
        int markedBits = 0;
        for (int i = 0; i < NUMBER_OF_BITS; i++) {
            int firstBit = (firstNum >> i) & 1;
            int secondBit = (secondNum >> i) & 1;
            if (firstBit != secondBit) {
                markedBits |= (1 << i); // Mark differing bits with 'X'
            }
        }

        for (int currNumIndex = 1; currNumIndex <= currentArray[0]; currNumIndex++) {
            int currNum = currentArray[currNumIndex];

            // Create a copy of the next array
            int* nextCopy = malloc((nextArray[0] + 1) * sizeof(int));
            memcpy(nextCopy, nextArray, (nextArray[0] + 1) * sizeof(int));

            for (int nextNumIndex = 1; nextNumIndex <= nextArray[0]; nextNumIndex++) {
                int nextNum = nextArray[nextNumIndex];

                int diffOneBits = 0;
                for (int i = 0; i < NUMBER_OF_BITS; i++) {
                    // Use the marked bits for comparison
                    if (!(markedBits & (1 << i))) {
                        int currBit = (currNum >> i) & 1;
                        int nextBit = (nextNum >> i) & 1;

                        if (currBit != nextBit) {
                            diffOneBits++;
                        }
                    }
                }
                
                if (diffOneBits == 1) {
                    // Check for duplicates before adding to the array
                    int alreadyOnArray = 0;
                    for (int i = 1; i <= currentCopy[0]; i++) {
                        if (currentCopy[i] == nextNum) {
                            alreadyOnArray = 1;
                            break;
                        }
                    }
                    
                    if (alreadyOnArray == 0) {
                        currentCopy[0]++; // Increment count of items in the array
                        currentCopy[currentCopy[0]] = nextNum;
                    }
                }
            }

            // Free the copy of the next array
            free(nextCopy);
        }

        // Update the original array with the modified copy
        free(stringsPointer[group]);
        stringsPointer[group] = currentCopy;
    }
}

void printstringsPointerValues(int** stringsPointer) {
    printf("Values in stringsPointer:\n");
    for (int i = 0; i < NUMBER_OF_BITS; i++) {
        printf("Array %d:", i);
        for (int j = 1; j <= stringsPointer[i][0]; j++) {
            printf(" %d", stringsPointer[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int listSize = argc;
    if (listSize < 2) {
        printf("\nArray list needed.");
        return 1;
    }

    char **stringsPointer = alocArrayList(listSize*3);
    for (int i = 1; i < listSize; i++) {
        convertToString(atoi(argv[i]), NUMBER_OF_BITS, stringsPointer);
    }

    for (int i = 0; i < NUMBER_OF_BITS; i++) {
        printf("\n%d have %d one(s)", i, stringsPointer[i][0]);
    }
    
    freeMemory(stringsPointer);
    return 0;
}