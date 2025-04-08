//
// Created by Artyom on 3/18/2025.
//

#include "utils.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void strncpy_if(char *dst, const char *src, size_t n, int(*f)(int)) {
	uint32_t i = 0;
	uint32_t j = 0;
	while (i < n && src[i]) {
		if (f(src[i])) {
			dst[j] = src[i];
			++j;
		}
		++i;
	}
	dst[j] = '\0';
}

void strtrim(char *str, const char *set) {
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

/*
 * returns a pointer to the n'th word in a string (starting from 0) delimited by a custom character
 * */
const char *goto_token(const char *s, const char delimiter, const uint32_t n) {
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

uint32_optional_t satoi(const char * const s)
{
	uint32_optional_t res = { .has_val = false, .val = -1 };

	for(uint8_t i = 0; s[i]; ++i) {
		if (!isdigit((uint8_t)s[i])) {
			return res;
		}
	}
	res.has_val = true;
	res.val = atoi(s);
	return res;
}

double_optional_t satof(const char * const s)
{
	double_optional_t res = { .has_val = false, .val = -1 };

	const uint8_t * t = (uint8_t *)s;

	while (*t && isdigit(*t)) {
		++t;
	}

	if (*t && *t == '.') {
		++t;
	}

	while(*t) {
		if (!isdigit(*t)) {
			return res;
		}
		++t;
	}
	res.has_val = true;
	res.val = atof(s);
	return res;
}
