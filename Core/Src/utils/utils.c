//
// Created by Artyom on 3/18/2025.
//

#include "utils.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void static_strtrim(char *str, const char *set) {
	if (!str || !set) {
		return;
	}

	uint32_t j = strlen(str) - 1;

	// "   foo bar   " -> "   foo bar"
	while(j > -1 && strchr(set, str[j])) {
		str[j] = '\0';
		--j;
	}

	j = 0;
	while (str[j] && strchr(set, str[j])) {
		++j;
	}

	uint32_t i = 0;

	// "  foo bar" -> "foo bar"
	while (str[j]) {
		str[i] = str[j];
		++i;
		++j;
	}

	while (str[i]) {
		str[i] = '\0';
		++i;
	}
}

int32_t stouint(const char* s, const char delimiter) {
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

uint8_t starts_with(const char *s1, const char *s2) {
  return (strncmp(s1, s2, strlen(s2)) == 0);
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
