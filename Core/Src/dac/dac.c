//
// Created by Artyom on 3/17/2025.
//

#include "dac.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

extern UART_HandleTypeDef huart1;
extern DAC_HandleTypeDef hdac;

static void dac_write(uint32_t dac_id, uint16_t dac_value) {

	static DAC_HandleTypeDef dac_map[DAC_COUNT] = {0};

	dac_map[0] = hdac;

	// mapping dac objects to id's with offset of 1. Dac with id 1 will be in the 0'th position.
	HAL_DAC_SetValue((dac_map + dac_id - 1), DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_value);
}

static int8_t handle_write(const char *message) {
	if (!message) {
		return -1;
	}

	const char *strid = goto_word(message, ' ', 2);
	const char *strvalue = goto_word(message, ' ', 3);

	if (NULL == strid || NULL == strvalue) {
		cli_writeline(&huart1, "error: invalid dac write command format. Type help for more details.");
		return CLI_ERROR;
	}

	const uint32_t dac_id = atoi(strid);

	if (-1 == dac_id) {
		cli_writeline(&huart1, "error: invalid dac id format. Available dac id's: [ 1 ]");
		return CLI_ERROR;
	} else if (dac_id != 1) {
		cli_writeline(&huart1, "error: invalid dac id value. Available dac id's: [ 1 ]");
		return CLI_ERROR;
	}


	const int32_t value = stouint(strvalue, ' ');

    if (value > 0 && value < DAC12_MAX) {
      dac_write(dac_id, value);
      return CLI_ERROR;
    }

    cli_writeline(&huart1, "error: invalid dac value format. Valid dac value range: [ 0 ... 4095 ].");
	return CLI_OK;
}

void dac_message_handler(const char *message) {

  if (!strcmp(message, "help")) {
    cli_writeline(&huart1, "to set DAC value, type `dac write <value>`");
  }

  else if (starts_with(message, "dac write ")) {
    handle_write(message);
  }

}


