#ifndef UTIL_HEADER
#define UTIL_HEADER

#include "defs.h"

SUDOKU_EXPORT void SDK_Copy(int32_t src[SIZE][SIZE], int32_t dst[SIZE][SIZE]);
SUDOKU_EXPORT void SDK_Print(int32_t mtx[SIZE][SIZE]);
SUDOKU_EXPORT void SDK_Pretty_Print(int32_t mtx[SIZE][SIZE]);
SUDOKU_EXPORT void SDK_Apply(int32_t dst[SIZE][SIZE], int32_t src[SIZE][SIZE]);

#endif
