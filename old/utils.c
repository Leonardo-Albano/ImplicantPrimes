#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NUMBER_OF_BITS = 5;

int** alocArrayList(int listSize){
    int **stringsPointer = malloc(NUMBER_OF_BITS * sizeof(int *));
    for (int i = 0; i < NUMBER_OF_BITS; i++) {
        stringsPointer[i] = malloc((listSize + 1) * sizeof(int)); // Corrected malloc size
        stringsPointer[i][0] = 0;
    }
    return stringsPointer;
}

void convertToString(int num, int numBits, char*** stringsPointer) {
    int countOnes = 0;
    for (int i = numBits - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (bit == 1) {
            countOnes++;
        }
        // printf("%d", bit);
    }
    
    char* numString = (char*)malloc((numBits + 1) * sizeof(char)); // Allocate memory for the string
    snprintf(numString, numBits + 1, "%d", num); // Convert the number to a string
    
    (*stringsPointer)[countOnes][0]++; // Increment count of items in the array
    (*stringsPointer)[countOnes][(*stringsPointer)[countOnes][0]] = numString; // Store the string in the array
    
    printf("%d - Have %d Ones\n", num, countOnes);
}

void freeMemory(char **stringsPointer){
    for (int i = 0; i < NUMBER_OF_BITS; i++) {
        free(stringsPointer[i]);
    }
    free(stringsPointer);
}
