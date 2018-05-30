#include "convert.h"

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "field.h"

void SDK_Import(int32_t mtx[SIZE][SIZE]) {
  assert(mtx != NULL);

  for (int32_t a = 0; a < SIZE; a++) {
    for (int32_t b = 0; b < SIZE; b++) {
      mtx[b][a] = translate_field(mtx[b][a]);
    }
  }
}
