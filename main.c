#include "sort.h"
#include <asm-generic/errno.h>
#include <raylib.h>
#include <stdbool.h>
//#include <stdio.h>
#include <stdlib.h>

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
  const char *name_sorter[] = {"quicksort", "insertionsort", "stalinsort"};
  int end = sizeof(name_sorter) / sizeof(name_sorter[0]);

  InitWindow(screenWidth, screenHeight, "sorting");

  SetTargetFPS(60);
  // quickSortStepIterative(array, arraysize, 0, arraysize - 1);
  while (!WindowShouldClose()) {
    if (!arraySorted(array, arraysize)){
      shuffle(array, arraysize);
    }
    
      if(IsKeyReleased(KEY_DOWN)){
        if (selected < end - 1){
        selected++;
      }
    }
   
      if(IsKeyReleased(KEY_UP)){ 
        if (selected > start){
        selected--;
      }
    }
    if (IsKeyReleased(KEY_ENTER)){
    switch (selected) {
        case 0:
        quickSortStepIterative(array, arraysize, 0, arraysize - 1);
        break;
        case 1:
        insertionSortStepIterative(array, arraysize);
        break;
        case 2:
        stalinSortStepIterative(array, arraysize);
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
        DrawText(name_sorter[i], text_size, text_size * i, text_size, RED);
      }
      if (i != selected) {
        DrawText(name_sorter[i], text_size, text_size * i, text_size, BLACK);
      }
    }
    EndDrawing();
  }
  free(array);
  CloseWindow();

  return 0;
}
