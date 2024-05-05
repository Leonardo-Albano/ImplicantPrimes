#ifndef UTILS_H
#define UTILS_H

extern int NUMBER_OF_BITS;

int** alocArrayList(int listSize);
void convertToString(int num, int numBits, char** stringsPointer);
void freeMemory(char **stringsPointer);

#endif 