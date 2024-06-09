#ifndef SORT_H
#define SORT_H
#include <stdlib.h>
#include <stdbool.h>
int *populate_crescente(int size);
//void reset_crescente(int *array, int size);
void shuffle(int *array, int arraysize);
bool isarraysorted(int* arr, int n);
//void quickSort(int *arr, int low, int high);
void QuickSortStepIterative(int *array, int arraysize, int low, int high);
//void insertionsort(int *array, int arraysize);
void InsertionSortStepIterative(int *array, int arraysize);
//void stalinsort(int *array, int arraysize);
void StalinSortStepIterative(int *array, int arraysize);
//void bogosort(int *array, int arraysize);
void BogoSortStepIterative(int *array, int arraysize);
#endif