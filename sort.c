#include "sort.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
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
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
void shuffle(int *arr, int n) {
  srand(time(NULL));

  for (int i = n - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    swap(&arr[i], &arr[j]);
  }
}
bool isarraysorted(int *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      return false;
    }
  }
  return true;
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
void QuickSortStepIterative(int *arr, int arrsize, int low, int high) {
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

    if (isarraysorted(arr, arrsize)) {
      sleep(1);
      return;
    }

    QuickSortStepIterative(arr, arrsize, low, partitionIndex - 1);
    QuickSortStepIterative(arr, arrsize, partitionIndex + 1, high);
  }
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
void InsertionSortStepIterative(int *array, int arraysize) {
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
void selectionsort(int *array, int arraysize) {
  int index = 0;
  while (!isarraysorted(array, arraysize)) {
    for (int j = 0; j < arraysize; j++) {
      if (array[j] == index) {
        swap(&array[j], &array[index]);
        index++;
      }
    }
  }
}
void SelectionSortStepIterative(int *array, int arraysize) {
  int index = 0;
  while (!isarraysorted(array, arraysize)) {
    for (int j = 0; j < arraysize; j++) {
      if (array[j] == index) {
        swap(&array[j], &array[index]);
        index++;
      }
    }
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
void merge(int arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  // Create temp arrays
  int L[n1], R[n2];

  // Copy data to temp arrays
  // L[] and R[]
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  // Merge the temp arrays back
  // into arr[l..r]
  // Initial index of first subarray
  i = 0;

  // Initial index of second subarray
  j = 0;

  // Initial index of merged subarray
  k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  // Copy the remaining elements
  // of L[], if there are any
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  // Copy the remaining elements of
  // R[], if there are any
  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}
// l is for left index and r is
// right index of the sub-array
// of arr to be sorted
void mergesort(int arr[], int l, int r) {
  if (l < r) {
    // Same as (l+r)/2, but avoids
    // overflow for large l and r
    int m = l + (r - l) / 2;

    // Sort first and second halves
    mergesort(arr, l, m);
    mergesort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
}
void MergeSortStepIterative(int *array, int arraysize, int l, int r) {
  // merge dont break
  if (l < r) {
    int m = l + (r - l) / 2;

    MergeSortStepIterative(array, arraysize, l, m);
    MergeSortStepIterative(array, arraysize, m + 1, r);

    merge(array, l, m, r);

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

    if (isarraysorted(array, arraysize)) {
      sleep(1);
    }
  }
}
int getMax(int arr[], int n) {
  int mx = arr[0];
  for (int i = 1; i < n; i++)
    if (arr[i] > mx)
      mx = arr[i];
  return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int arr[], int n, int exp) {
  // output array
  int output[n];
  int i, count[10] = {0};

  // Store count of occurrences in count[]
  for (i = 0; i < n; i++)
    count[(arr[i] / exp) % 10]++;

  // Change count[i] so that count[i] now contains actual
  // position of this digit in output[]
  for (i = 1; i < 10; i++)
    count[i] += count[i - 1];

  // Build the output array
  for (i = n - 1; i >= 0; i--) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }

  // Copy the output array to arr[], so that arr[] now
  // contains sorted numbers according to current digit
  for (i = 0; i < n; i++)
    arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(int arr[], int n) {
  // Find the maximum number to know number of digits
  int m = getMax(arr, n);

  // Do counting sort for every digit. Note that instead
  // of passing digit number, exp is passed. exp is 10^i
  // where i is current digit number
  for (int exp = 1; m / exp > 0; exp *= 10)
    countSort(arr, n, exp);
}
void RadixSortStepIterative(int *array, int arraysize) {
  int m = getMax(array, arraysize);

  for (int exp = 1; m / exp > 0; exp *= 10) {
    countSort(array, arraysize, exp);

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

    // is fast
    sleep(1);

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
void StalinSortStepIterative(int *array, int arraysize) {
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
void bogosort(int *array, int arraysize) {
  while (!isarraysorted(array, arraysize)) {
    shuffle(array, arraysize);
  }
}
void BogoSortStepIterative(int *array, int arraysize) {
  while (!isarraysorted(array, arraysize)) {
    if (WindowShouldClose()) {
      return;
    }
    shuffle(array, arraysize);
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
  }
  sleep(1);
}
