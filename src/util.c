#include "util.h"

#include "field.h"

void SDK_Copy(int32_t src[SIZE][SIZE], int32_t dst[SIZE][SIZE]) {
  for (int32_t a = 0; a < SIZE; a++) {
    for (int32_t b = 0; b < SIZE; b++) {
      dst[a][b] = src[a][b];
    }
  }
}

void SDK_Print(int32_t mtx[SIZE][SIZE]) {
  for (int32_t a = 0; a < SIZE; a++) {
    for (int32_t b = 0; b < SIZE; b++) {
      printf("%d ", mtx[a][b]);
    }

    printf("\n");
  }
}

void SDK_Pretty_Print(int32_t mtx[SIZE][SIZE]) {
  for (int32_t a = 0; a < SIZE; a++) {
    for (int32_t b = 0; b < SIZE; b++) {
      printf("%d ", to_pretty(mtx[a][b]));
    }

    printf("\n");
  }
}

void SDK_Apply(int32_t dst[SIZE][SIZE], int32_t src[SIZE][SIZE]) {
  for (int32_t a = 0; a < SIZE; a++) {
    for (int32_t b = 0; b < SIZE; b++) {
      dst[a][b] &= src[a][b];
    }
  }
}
