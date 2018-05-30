#ifndef FIELD_HEADER
#define FIELD_HEADER

#include <stdint.h>
#include <stdbool.h>

bool is_field_literal(int32_t field);
bool is_field_empty(int32_t field);

int32_t to_pretty(int32_t field);
int32_t translate_field(int32_t field);

#endif
