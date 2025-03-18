//
// Created by Artyom on 3/17/2025.
//

#include "dac.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

extern UART_HandleTypeDef huart1;
extern volatile uint16_t dac_value;

static int32_t parse_expr(const char* s) {
  if (!s) {
    return -1;
  }
  const int32_t res = atoi(s);
  while (isdigit((uint8_t)*s)) {
    ++s;
  }
  return (*s == '\0') ? res : -1;
}

static void dac_cli_handler(const char *message) {

  if (!strcmp(message, "help")) {
    cli_putsnl(&huart1, "to set DAC value, type `dac set <12 bit value>`");

  }

  else if (!strncmp(message, "dac set ", strlen("dac set "))) {
    const uint32_t value = parse_expr(message + strlen("dac set "));
    if (-1 != value && value < DAC12_MAX) {
      dac_value = value;
    }
  }

  else {
    cli_putsnl(&huart1, "error: command not found");
  }
}

void dac_cli() {
  cli_engine(&huart1, dac_cli_handler);
}
