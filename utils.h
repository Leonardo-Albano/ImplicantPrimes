#ifndef UTILS_H
#define UTILS_H

extern int NUMBER_OF_BITS;

char** alocArrayList(int listSize);
void convertToString(int iterationIndex, int num, char*** stringsPointer);
char*** groupByOnes(char** stringsPointer, int listSize, int* mintermGroups, int* lastIndexGroups);
char*** alocPrimesGroups(int listSize);
void printPrimesGroups(int* lastIndexGroups, char*** primesGroups);

void groupMinterms(int* lastIndexGroups, char*** primesGroups);

void freeMemory(char **stringsPointer, int* counts, int numStrings);
void freeMemoryGroups(char ***groups, int* counts, int numGroups);

#endif 