#include "breakdown.h"

#include <assert.h>

#include "field.h"

bool SDK_Check_Breakdown(int32_t mtx[SIZE][SIZE]) {
  assert(mtx != NULL);

  for (int32_t a = 0; a < SIZE; ++a) {
    for (int32_t b = 0; b < SIZE; ++b) {
      int32_t field = mtx[a][b];

      if (!is_field_literal(field)) {
        return false;
      }
    }
  }

  return true;
}
