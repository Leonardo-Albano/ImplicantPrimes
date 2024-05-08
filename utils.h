#ifndef UTILS_H
#define UTILS_H

extern int NUMBER_OF_BITS;

typedef struct {
    char* binaryRepresentation;
    int* originalNumbers;
    int countOfOnes;
} Minterm;

Minterm** allocMintermList(int listSize);
Minterm* allocMinterm();
void convertToString(int iterationIndex, int num, Minterm** mintermsList);
Minterm*** groupByOnes(Minterm **mintermsList, int listSize, int* mintermGroups, int* lastIndexGroups, int iteration);
Minterm*** allocPrimesGroups(int listSize);
void printPrimesGroups(int* lastIndexGroups, Minterm*** primesGroups);

Minterm*** groupMinterms(int* lastIndexGroups, Minterm**** primesGroups, int* listSize);

void freeMemory(char **stringsPointer, int* counts, int numStrings);
void freeMemoryGroups(char ***groups, int* counts, int numGroups);
void freeMintermsList(Minterm** mintermsList, int numMinterms);

Minterm** flattenPrimesGroups(Minterm*** primesGroups, int* lastIndexGroups, Minterm** newMintermsList);

#endif 