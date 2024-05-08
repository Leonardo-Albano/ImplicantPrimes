#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NUMBER_OF_BITS = 4;

Minterm*** allocPrimesGroups(int listSize) {
    Minterm*** primesGroups = malloc(NUMBER_OF_BITS * sizeof(Minterm**));
    if (primesGroups == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= NUMBER_OF_BITS; i++) {  // Include the group for zero ones
        primesGroups[i] = malloc(listSize * sizeof(Minterm*));
        if (primesGroups[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    return primesGroups;
}

Minterm* allocMinterm() {
    Minterm* minterm = malloc(sizeof(Minterm));
    if (minterm == NULL) {
        fprintf(stderr, "Memory allocation failed for Minterm.\n");
        exit(EXIT_FAILURE);
    }

    minterm->binaryRepresentation = malloc((NUMBER_OF_BITS + 1) * sizeof(char));
    if (minterm->binaryRepresentation == NULL) {
        fprintf(stderr, "Memory allocation failed for binaryRepresentation.\n");
        exit(EXIT_FAILURE);
    }

    minterm->originalNumbers = malloc(NUMBER_OF_BITS * sizeof(int));
    if (minterm->originalNumbers == NULL) {
        fprintf(stderr, "Memory allocation failed for originalNumbers.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the binaryRepresentation array to zeros
    for (int i = 0; i < NUMBER_OF_BITS; i++) {
        minterm->binaryRepresentation[i] = '0';
        minterm->originalNumbers[i] = 0;
    }
    minterm->binaryRepresentation[NUMBER_OF_BITS] = '\0'; // Null-terminate the string

    return minterm;
}

void convertToString(int iterationIndex, int num, Minterm** mintermsList) {
    char* binaryString = (char*)malloc((NUMBER_OF_BITS + 1) * sizeof(char));
    if (binaryString == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    int countOfOnes = 0;
    int leastSignificantBit = NUMBER_OF_BITS - 1;

    for (int i = leastSignificantBit; i >= 0; i--) {
        int bit = (num >> i) & 1;
        binaryString[leastSignificantBit - i] = bit + '0';  // Convert bit to character ('0' or '1')

        if (bit == 1) {
            countOfOnes++;  // Increment count if the bit is '1'
        }
    }
    binaryString[NUMBER_OF_BITS] = '\0';

    mintermsList[iterationIndex]->originalNumbers[0] = num;
    mintermsList[iterationIndex]->binaryRepresentation = binaryString;
    mintermsList[iterationIndex]->countOfOnes = countOfOnes;
}

Minterm*** groupByOnes(Minterm **mintermsList, int listSize, int* mintermGroups, int* lastIndexGroups, int iteration) {
    Minterm*** primesGroups = allocPrimesGroups(listSize);

    for (int i = 0; i < listSize; i++) {
        int countOfOnes = mintermsList[i]->countOfOnes;
        printf("\nCount of ones: %s\n", mintermsList[i]->binaryRepresentation);
        Minterm* minterm = malloc(sizeof(Minterm));
        if (minterm == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        // Allocate memory for binaryRepresentation and copy the values
        minterm->binaryRepresentation = malloc((NUMBER_OF_BITS + 1) * sizeof(char));
        strcpy(minterm->binaryRepresentation, mintermsList[i]->binaryRepresentation);

        // Allocate memory for originalNumbers array
        minterm->originalNumbers = malloc(iteration * sizeof(int));
        for (int original_num_index = 0; original_num_index < iteration; original_num_index++)
        {
            minterm->originalNumbers[original_num_index] = mintermsList[i]->originalNumbers[original_num_index];  // Assuming binary strings represent integers
        }
        

        primesGroups[countOfOnes][lastIndexGroups[countOfOnes]++] = minterm;  // Save the address of the minterm
        printf("\nteste\n");
    }

    return primesGroups;
}


void printPrimesGroups(int* lastIndexGroups, Minterm*** primesGroups) {
    for (int group = 0; group <= NUMBER_OF_BITS-1; group++) { //dont print the last group
        printf("Group %d (Count of Ones: %d):\n", group, group);
        for (int i = 0; i < lastIndexGroups[group]; i++) {
            printf("%s\n", primesGroups[group][i]->binaryRepresentation);
        }
    }
}

Minterm** allocMintermList(int listSize) {
    Minterm** mintermList = malloc(listSize * sizeof(Minterm*));
    if (mintermList == NULL) {
        fprintf(stderr, "Memory allocation failed for Minterm list.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize each Minterm instance in the list
    for (int i = 0; i < listSize; i++) {
        mintermList[i] = allocMinterm();
    }

    return mintermList;
}

Minterm*** groupMinterms(int* lastIndexGroups, Minterm**** primesGroups, int* listSize) {
    Minterm*** newPrimesGroups = allocPrimesGroups(NUMBER_OF_BITS);
    int newLastIndexGroups[NUMBER_OF_BITS];
    for (int i = 0; i < NUMBER_OF_BITS; i++) {
        newLastIndexGroups[i] = 0;
    }

    int totalMinterms = 0;
    for (int group = 0; group < NUMBER_OF_BITS; group++) {
        printf("\nInitiating group %d\n", group);
        Minterm** currentGroup = (*primesGroups)[group];
        Minterm** nextGroup = (*primesGroups)[group + 1];

        for (int currentPrimeIndex = 0; currentPrimeIndex < lastIndexGroups[group]; currentPrimeIndex++) {
            Minterm* currentPrime = currentGroup[currentPrimeIndex];

            for (int nextPrimeIndex = 0; nextPrimeIndex < lastIndexGroups[group + 1]; nextPrimeIndex++) {
                Minterm* nextPrime = nextGroup[nextPrimeIndex];

                int differentBit = NUMBER_OF_BITS + 1; // Set a unreachable bit
                int diffBitsCount = 0;

                for (int bit = 0; bit < NUMBER_OF_BITS; bit++) {
                    if (currentPrime->binaryRepresentation[bit] != nextPrime->binaryRepresentation[bit]) {
                        diffBitsCount++;
                        differentBit = bit;
                    }
                }

                if (diffBitsCount == 1) {
                    // Create a new combined minterm
                    Minterm* newMinterm = malloc(sizeof(Minterm));
                    if (newMinterm == NULL) {
                        fprintf(stderr, "Memory allocation failed.\n");
                        exit(EXIT_FAILURE);
                    }
                    // Allocate memory for binaryRepresentation and copy the values
                    newMinterm->binaryRepresentation = malloc((NUMBER_OF_BITS + 1) * sizeof(char));
                    strcpy(newMinterm->binaryRepresentation, currentPrime->binaryRepresentation);
                    newMinterm->binaryRepresentation[differentBit] = 'x';

                    // Allocate memory for originalNumbers array
                    newMinterm->originalNumbers = malloc(2 * sizeof(int));
                    newMinterm->originalNumbers[0] = currentPrime->originalNumbers[0];
                    newMinterm->originalNumbers[1] = nextPrime->originalNumbers[0];
                    
                    if (currentPrime->countOfOnes > nextPrime->countOfOnes) {
                        newMinterm->countOfOnes = currentPrime->countOfOnes - 1;
                    } else {
                        newMinterm->countOfOnes = nextPrime->countOfOnes - 1;
                    }

                    newPrimesGroups[group][newLastIndexGroups[group]++] = newMinterm;
                    printf("%s-%s different in one = %s\n", currentPrime->binaryRepresentation, nextPrime->binaryRepresentation, newMinterm->binaryRepresentation);
                    totalMinterms++;
                }
            }
        }
    }

    for (int i = 0; i < NUMBER_OF_BITS; i++) {
        lastIndexGroups[i] = newLastIndexGroups[i];
    }

    *listSize = totalMinterms;
    return newPrimesGroups;
}

void freeMemory(char **mintermsList, int* counts, int numStrings) {
    if (mintermsList != NULL) {
        for (int i = 0; i < numStrings; i++) {
            free(mintermsList[i]);
        }
        free(mintermsList);
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

void freeMintermsList(Minterm** mintermsList, int numMinterms) {
    if (mintermsList != NULL) {
        for (int i = 0; i < numMinterms; i++) {
            if (mintermsList[i] != NULL) {
                free(mintermsList[i]->binaryRepresentation);
                free(mintermsList[i]->originalNumbers);
                free(mintermsList[i]);
            }
        }
        free(mintermsList);
    }
}

Minterm** flattenPrimesGroups(Minterm*** primesGroups, int* lastIndexGroups, Minterm** newMintermsList) {
    int index = 0;
    for (int group = 0; group <= NUMBER_OF_BITS; group++) {
        for (int i = 0; i < lastIndexGroups[group]; i++) {
            newMintermsList[index++] = primesGroups[group][i];
        }
    }

    return newMintermsList;
}