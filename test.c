#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void selectionsort(int *array, int arraysize) {
  for (int i = 0; i < arraysize; i++) {
    for (int j = 0; j < arraysize; j++) {
      if (array[j] == i) {
        swap(&array[j], &array[i]);
      }
    }
  }
}

int *populate_crescente(int size) {
  int *arr = malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
    arr[i] = i;
  }
  return arr;
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

int main() {
  const int size = 10;
  int *array = populate_crescente(size);
  shuffle(array, size);
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n\n");
  // stalinSort(array, size);
  selectionsort(array, size);
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}