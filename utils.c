#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NUMBER_OF_BITS = 4;

char** alocArrayList(int listSize){
    char **stringsPointer = malloc(listSize * sizeof(char *));

    if (stringsPointer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < listSize; i++) {

        int additionalBits = 2; // One to the \0, and another to the count of ones
        stringsPointer[i] = malloc((NUMBER_OF_BITS + additionalBits) * sizeof(char));
        if (stringsPointer[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

    }

    return stringsPointer;
}

void convertToString(int iterationIndex, int num, char*** stringsPointer) {

    char* binaryString = (char*)malloc((NUMBER_OF_BITS + 1) * sizeof(char));
    if (binaryString == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    int onesCount = 0;
    int leastSignificantBit = NUMBER_OF_BITS - 1;

    for (int i = leastSignificantBit; i >= 0; i--) {
        int bit = (num >> i) & 1;
        binaryString[leastSignificantBit - i] = bit + '0';  // Convert bit to character ('0' or '1')

        if (bit == 1) {
            onesCount++;  // Increment count if the bit is '1'
        }
    }
    binaryString[NUMBER_OF_BITS] = '\0';

    (*stringsPointer)[iterationIndex][0] = onesCount + '0';  // Convert to character
    strcpy(&((*stringsPointer)[iterationIndex][1]), binaryString);  // Copy binaryString after the count

    free(binaryString);
}

char*** groupByOnes(char** stringsPointer, int listSize, int* mintermGroups, int* lastIndexGroups) {

    char*** primesGroups = alocPrimesGroups(listSize);

    for (int i = 0; i < listSize; i++) {
        int countOfOnes = stringsPointer[i][0] - '0';  // Convert character back to integer

        // primesGroups[countOfOnes][mintermGroups[countOfOnes]] = &stringsPointer[i][1];  // Save the address of the string
        primesGroups[countOfOnes][lastIndexGroups[countOfOnes]] = &stringsPointer[i][1];  // Save the address of the string
        lastIndexGroups[countOfOnes]++;
        // mintermGroups[countOfOnes]++;
    }

    return primesGroups;
}

char*** alocPrimesGroups(int listSize){
    char*** primesGroups = malloc((NUMBER_OF_BITS) * sizeof(char**));
    if (primesGroups == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i <= NUMBER_OF_BITS; i++) {  // Include the group for zero ones
        primesGroups[i] = malloc(listSize * sizeof(char*));
        if (primesGroups[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    return primesGroups;
}

void printPrimesGroups(int* lastIndexGroups, char*** primesGroups){
    for (int group = 0; group <= NUMBER_OF_BITS; group++) {
        printf("Group %d (Count of Ones: %d):\n", group, group);
        for (int i = 0; i < lastIndexGroups[group]; i++) {
            printf("%s\n", primesGroups[group][i]);
        }
    }
}

void groupMinterms(int* lastIndexGroups, char*** primesGroups) {
    for (int group = 0; group < NUMBER_OF_BITS; group++) {
        printf("Initiating group %d\n", group);
        char** currentGroup = primesGroups[group];
        char** nextGroup = primesGroups[group+1];
        
        for (int currentPrimeIndex = 0; currentPrimeIndex < lastIndexGroups[group]; currentPrimeIndex++)
        {
            char* currentPrime = currentGroup[currentPrimeIndex];
            char* currentPrimeCopy = malloc((strlen(currentPrime) + 1) * sizeof(char));

            for (int nextPrimeIndex = 0; nextPrimeIndex < lastIndexGroups[group+1]; nextPrimeIndex++)
            {
                char* nextPrime = nextGroup[nextPrimeIndex];
                char* nextPrimeCopy = malloc((strlen(nextPrime) + 1) * sizeof(char));
                
                strcpy(currentPrimeCopy, currentPrime);
                strcpy(nextPrimeCopy, nextPrime);

                int differentBit = NUMBER_OF_BITS + 1;
                int diffBitsCount = 0;

                for (int bit = 0; bit < NUMBER_OF_BITS; bit++)
                {
                    if(currentPrime[bit] != nextPrime[bit]){
                        diffBitsCount++;
                        differentBit = bit;        
                    }
                }

                if(diffBitsCount == 1){
                    currentPrimeCopy[differentBit] = 'x';
                    nextPrimeCopy[differentBit] = 'x';

                    printf("%s-%s different in one\n", currentPrimeCopy, nextPrimeCopy);
                }
            }
        }
    }
    printf("\nfinished!\n");
    //Continuar implementando essa parte, precisa salvar o binário com o x no lugar do binário real (talvez com um realoc igual ta no print)
    //Precisa criar um array para salvar os valores representados nesse array
}

void freeMemory(char **stringsPointer, int* counts, int numStrings) {
    if (stringsPointer != NULL) {
        for (int i = 0; i < numStrings; i++) {
            free(stringsPointer[i]);
        }
        free(stringsPointer);
    }
    if (counts != NULL) {
        free(counts);
    }
}

void freeMemoryGroups(char ***groups, int* counts, int numGroups) {
    if (groups != NULL) {
        for (int i = 0; i < numGroups; i++) {
            if (groups[i] != NULL) {
                for (int j = 0; j < counts[i]; j++) {
                    free(groups[i][j]);  // Free memory for each string in the group
                }
                free(groups[i]);  // Free memory for the group
            }
        }
        free(groups);  // Free memory for the groups array
    }
    if (counts != NULL) {
        free(counts);  // Free memory for the counts array
    }
}
