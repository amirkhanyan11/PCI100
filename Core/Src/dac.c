//
// Created by Artyom on 3/17/2025.
//

#include "dac.h"
#include "cli.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

extern UART_HandleTypeDef huart1;
extern DAC_HandleTypeDef hdac;

static void dac_write(uint16_t dac_value) {
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_value);
}

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

uint8_t dac_message_handler(const char *message) {

  if (!strcmp(message, "help")) {
    cli_writeline(&huart1, "to set DAC value, type `dac write <value>`");
    return CLI_OK;
  }

  else if (starts_with(message, "dac write ")) {
    const uint32_t value = parse_expr(message + strlen("dac write "));
    if (-1 != value && value < DAC12_MAX) {
      dac_write(value);
    }
    return CLI_OK;
  }

  return CLI_COMMAND_NOT_FOUND;
}


