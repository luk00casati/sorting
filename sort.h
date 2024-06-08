#ifndef SORT_H
#define SORT_H
#include <stdlib.h>
#include <stdbool.h>
int *populate_crescente(int size);
void reset_crescente(int *array, int size);
void shuffle(int *array, size_t n);
bool arraySorted(int* arr, int n);
void quickSort(int *arr, int low, int high);
void quickSortStepIterative(int *array, int arraysize, int low, int high);
void insertionsort(int *array, int arraysize);
void insertionSortStepIterative(int *array, int arraysize);
void stalinsort(int *array, int arraysize);
void stalinSortStepIterative(int *array, int arraysize);
#endif