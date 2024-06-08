#include "sort.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

int *populate_crescente(int size) {
  int *arr = malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
    arr[i] = i;
  }
  return arr;
}
void reset_crescente(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    arr[i] = i;
  }
}
void shuffle(int *array, size_t n) {
  if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}
bool arraySorted(int *arr, int n) {
  // Array has one or no element
  if (n == 0 || n == 1)
    return false;

  for (int i = 1; i < n; i++) {
    // Unsorted pair found
    if (arr[i - 1] > arr[i])
      return true;
  }

  // No unsorted pair found
  return false;
}
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
int partition(int arr[], int low, int high) {

  // initialize pivot to be the first element
  int pivot = arr[low];
  int i = low;
  int j = high;

  while (i < j) {

    // condition 1: find the first element greater than
    // the pivot (from starting)
    while (arr[i] <= pivot && i <= high - 1) {
      i++;
    }

    // condition 2: find the first element smaller than
    // the pivot (from last)
    while (arr[j] > pivot && j >= low + 1) {
      j--;
    }
    if (i < j) {
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[low], &arr[j]);
  return j;
}
void quickSort(int arr[], int low, int high) {
  if (low < high) {

    // call Partition function to find Partition Index
    int partitionIndex = partition(arr, low, high);

    // Recursively call quickSort() for left and right
    // half based on partition Index
    quickSort(arr, low, partitionIndex - 1);
    quickSort(arr, partitionIndex + 1, high);
  }
}
void quickSortStepIterative(int *arr, int arrsize, int low, int high) {
  if (low < high) {
    if (WindowShouldClose()) {
      shuffle(arr, arrsize);
      return;
    }

    int partitionIndex = partition(arr, low, high);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = 0; i < arrsize + 1; i++) {
      int rectHeight = (arr[i] * GetScreenHeight()) / arrsize;
      DrawRectangle(i, GetScreenHeight() - rectHeight, 1, rectHeight, RED);
    }
    EndDrawing();

    quickSortStepIterative(arr, arrsize, low, partitionIndex - 1);
    quickSortStepIterative(arr, arrsize, partitionIndex + 1, high);
  }
  sleep(1);
}
void insertionsort(int *array, int arraysize) {
  int i, key, j;
  for (i = 1; i < arraysize; i++) {
    key = array[i];
    j = i - 1;

    /* Move elements of arr[0..i-1], that are
      greater than key, to one position ahead
      of their current position */
    while (j >= 0 && array[j] > key) {
      array[j + 1] = array[j];
      j = j - 1;
    }
    array[j + 1] = key;
  }
}
void insertionSortStepIterative(int *array, int arraysize) {
  int i, key, j;
  for (i = 1; i < arraysize; i++) {
    key = array[i];
    j = i - 1;
    while (j >= 0 && array[j] > key) {
      array[j + 1] = array[j];
      j = j - 1;
    }
    array[j + 1] = key;
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = 0; i < arraysize + 1; i++) {
      int rectHeight = (array[i] * GetScreenHeight()) / arraysize;
      DrawRectangle(i, GetScreenHeight() - rectHeight, 1, rectHeight, RED);
    }
    EndDrawing();
    if (WindowShouldClose()) {
      shuffle(array, arraysize);
      return;
    }
  }
  sleep(1);
}
void stalinsort(int *array, int arraysize) {
  int lastValid = array[0];
  int index = 1;

  for (int i = 1; i < arraysize; i++) {
    if (array[i] < lastValid) {
      array[i] = -1;
    } else {
      lastValid = array[i];
      array[index] = array[i];
      index++;
      array[i] = -1;
    }
  }
}
void stalinSortStepIterative(int *array, int arraysize) {
  int lastValid = array[0];
  int index = 1;

  for (int i = 1; i < arraysize; i++) {
    if (array[i] < lastValid) {
      array[i] = -1;
    } else {
      lastValid = array[i];
      array[index] = array[i];
      index++;
      array[i] = -1;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int j = 0; j < arraysize; j++) {
      if (array[j] != -1) {
        int rectHeight = (array[j] * GetScreenHeight()) / arraysize;
        DrawRectangle(j * (GetScreenWidth() / arraysize),
                      GetScreenHeight() - rectHeight,
                      GetScreenWidth() / arraysize, rectHeight, RED);
      }
    }

    EndDrawing();

    if (WindowShouldClose()) {
      shuffle(array, arraysize);
      return;
    }
  }
  reset_crescente(array, arraysize);
  sleep(1);
}