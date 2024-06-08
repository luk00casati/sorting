#include <stdlib.h>
#include <stdio.h>

void stalinSort(int* array, int arraysize) {
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

int main(){
  const int size = 10;
  int * array = populate_crescente(size);
  shuffle(array, size);
  for (int i = 0; i < size; i++){
    printf("%d ", array[i]);
  }
  printf("\n\n");
  stalinSort(array, size);
    for (int i = 0; i < size; i++){
    printf("%d ", array[i]);
  }
  printf("\n");
}