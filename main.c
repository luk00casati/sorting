#include "sort.h"
#include <raylib.h>
#include <stdbool.h>
// #include <stdio.h>
#include <stdlib.h>

#define ARRSIZE(x) sizeof(x) / sizeof(x[0])

#define FOREACH_SORTER_ALG(SORTER_ALG)                                         \
  SORTER_ALG(quicksort)                                                        \
  SORTER_ALG(insertionsort)                                                    \
  SORTER_ALG(selectionsort)                                                    \
  SORTER_ALG(mergesort)                                                        \
  SORTER_ALG(radixsort)                                                        \
  SORTER_ALG(stalinsort)                                                       \
  SORTER_ALG(bogosort)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;
  const int text_size = 40;
  const int arraysize = screenWidth;
  int *array = populate_crescente(arraysize);
  // quickSort(array, 0, arraysize-1);
  // insertionsort(array, arraysize);

  // select menu
  int selected = 0;
  int start = 0;
  enum SORTER_ENUM { FOREACH_SORTER_ALG(GENERATE_ENUM) };
  static const char *SORTER_STRING[] = {FOREACH_SORTER_ALG(GENERATE_STRING)};
  int end = ARRSIZE(SORTER_STRING);
  enum SORTER_ENUM sorter;

  InitWindow(screenWidth, screenHeight, "sorting");

  SetTargetFPS(60);
  // quickSortStepIterative(array, arraysize, 0, arraysize - 1);
  while (!WindowShouldClose()) {
    if (isarraysorted(array, arraysize)) {
      shuffle(array, arraysize);
    }

    if (IsKeyReleased(KEY_DOWN)) {
      if (selected < end - 1) {
        selected++;
      }
    }

    if (IsKeyReleased(KEY_UP)) {
      if (selected > start) {
        selected--;
      }
    }

    if (IsKeyReleased(KEY_ENTER)) {
      sorter = selected;
      switch (sorter) {
      case quicksort:
        QuickSortStepIterative(array, arraysize, 0, arraysize - 1);
        break;
      case insertionsort:
        InsertionSortStepIterative(array, arraysize);
        break;
      case selectionsort:
        SelectionSortStepIterative(array, arraysize);
        break;
      case mergesort:
        MergeSortStepIterative(array, arraysize, 0, arraysize - 1);
        break;
      case radixsort:
        RadixSortStepIterative(array, arraysize);
        break;
      case stalinsort:
        StalinSortStepIterative(array, arraysize);
        break;
      case bogosort:
        BogoSortStepIterative(array, arraysize);
        break;
      default:
        break;
      }
      selected = 0;
    }
    BeginDrawing();

    ClearBackground(RAYWHITE);

    for (int i = start; i < end; i++) {
      if (i == selected) {
        DrawText(SORTER_STRING[i], text_size, text_size * i, text_size, RED);
      }
      if (i != selected) {
        DrawText(SORTER_STRING[i], text_size, text_size * i, text_size, BLACK);
      }
    }
    EndDrawing();
  }
  free(array);
  CloseWindow();

  return 0;
}
