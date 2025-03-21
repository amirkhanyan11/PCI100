//
// Created by Artyom on 3/18/2025.
//

#ifndef LED_H
#define LED_H

#include "main.h"

#define UINT32_MAX_DIGITS 10

const char *static_itoa(uint32_t n);
const char *goto_word(const char *s, const char delimiter, const uint32_t n);
int32_t strtouint(const char* s, const char delimiter);


#endif //LED_H
