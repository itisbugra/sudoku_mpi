#include "field.h"

bool is_field_literal(int32_t field) {
  switch (field) {
    case 0b000000001:
    case 0b000000010:
    case 0b000000100:
    case 0b000001000:
    case 0b000010000:
    case 0b000100000:
    case 0b001000000:
    case 0b010000000:
    case 0b100000000:
      return true;
    default:
      return false;
  }
}

bool is_field_empty(int32_t field) {
  return field == 0;
}

int32_t to_pretty(int32_t field) {
  switch (field) {
    case 0b000000001:
      return 1;
    case 0b000000010:
      return 2;
    case 0b000000100:
      return 3;
    case 0b000001000:
      return 4;
    case 0b000010000:
      return 5;
    case 0b000100000:
      return 6;
    case 0b001000000:
      return 7;
    case 0b010000000:
      return 8;
    case 0b100000000:
      return 9;
    default:
      return 0;
  }
}

int32_t translate_field(int32_t fld) {
  switch (fld) {
    case 1:
      return 0b000000001;
    case 2:
      return 0b000000010;
    case 3:
      return 0b000000100;
    case 4:
      return 0b000001000;
    case 5:
      return 0b000010000;
    case 6:
      return 0b000100000;
    case 7:
      return 0b001000000;
    case 8:
      return 0b010000000;
    case 9:
      return 0b100000000;
    default:
      return 0b111111111;
  }
}
