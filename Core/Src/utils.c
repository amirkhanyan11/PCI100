//
// Created by Artyom on 3/18/2025.
//

#include "utils.h"
#include <stdlib.h>
#include <ctype.h>

int32_t strtouint(const char* s, const char delimiter) {
  if (!s) {
    return -1;
  }

  // skip all delimiters prior to the number
  while(*s == delimiter) {
	  ++s;
  }
  const int32_t res = atoi(s);
  while (isdigit((uint8_t)*s)) {
    ++s;
  }

  if (*s != '\0' && *s != delimiter) {
	  return -1;
  }

  return res;
}

/*
 * returns a pointer to the n'th word in a string (starting from 0) delimited by a custom character
 * */
const char *goto_word(const char *s, const char delimiter, const uint32_t n) {
	if (!s) {
		return NULL;
	}

	uint8_t isspace = 1;

	uint32_t i = 0;
	uint32_t word_count = 0;

	while (s[i]) {
		if (s[i] == delimiter) {
			isspace = 1;
		} else if (isspace) {
			isspace = 0;
			++word_count;
		}

		if (word_count == n + 1) {
			return s + i;
		}

		++i;
	}

	return NULL;
}

const char *static_itoa(uint32_t n) {
  static char res[UINT32_MAX_DIGITS + 1] = {0};
  uint8_t i = 0;

  while (n > 9) {
    res[i] = '0' + (n % 10);
    n /= 10;
    ++i;
  }
  res[i] = '0' + n;
  res[i + 1] = '\0';

  for (int8_t j = 0; j < i; ++j, --i) {
    const char t = res[j];
    res[j] = res[i];
    res[i] = t;
  }

  return res;
}
