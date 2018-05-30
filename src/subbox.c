#include "subbox.h"

#include <assert.h>
#include <stdlib.h>

#include "field.h"

void SDK_Mark_Subbox_Availables(int32_t mtx[SIZE][SIZE]) {
  assert(mtx != NULL);

  for (int32_t a = 0; a < SIZE_MULTIPLIER; ++a) {
    for (int32_t b = 0; b < SIZE_MULTIPLIER; ++b) {
      //  Find used numbers
      int32_t result = 0;

      for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
        for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
          int32_t field = mtx[(a * SIZE_MULTIPLIER) + c][(b * SIZE_MULTIPLIER) + d];

          if (is_field_literal(field)) {
            result |= field;
          }
        }
      }

      //  Insert unused numbers to empty fields
      int32_t unused_numbers = result ^ 0b111111111;

      for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
        for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
          if (!is_field_literal(mtx[(a * SIZE_MULTIPLIER) + c][(b * SIZE_MULTIPLIER) + d])) {
            mtx[(a * SIZE_MULTIPLIER) + c][(b * SIZE_MULTIPLIER) + d] &= unused_numbers;
          }
        }
      }
    }
  }
}
