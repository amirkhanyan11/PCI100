//
// Created by Artyom on 3/18/2025.
//

#ifndef LED_H
#define LED_H

#include "main.h"
#include "typedefs.h"
#include <stdbool.h>
#define UINT32_MAX_DIGITS 10


struct uint32_optional_s {
	bool has_val;
	uint32_t val;
};

struct double_optional_s {
	bool has_val;
	double val;
};

const char *static_itoa(uint32_t n);
const char *goto_token(const char *s, const char delimiter, const uint32_t n);
int32_t stouint(const char* s, const char delimiter);
void strtrim(char *str, const char *set);
void strncpy_if(char *dst, const char *src, size_t n, int(*f)(int));
uint32_optional_t satoi(const char * const s);
double_optional_t satof(const char * const s);

#endif //LED_H
