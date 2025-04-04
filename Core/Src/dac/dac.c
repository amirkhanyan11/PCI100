//
// Created by Artyom on 3/17/2025.
//

#include "dac.h"
#include "../cli/cli.h"
#include "../cli/cli_string_literals.h"
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

extern UART_HandleTypeDef huart1;
extern DAC_HandleTypeDef hdac;

uint8_t exec_dac(cmd_t * const cmd) {

	const char * const option = cmd->argv[0];

	if (!strcmp(option, "write")) {
		return dac_write(cmd);
	}

	printf(CLI_COMMAND_NOT_FOUND);
	return 127;
}

uint8_t dac_write(cmd_t * const cmd) {

	if (cmd->argc != 3) {
		printf("dac: write: %s", CLI_INVALID_OPTIONS);
		return EINVAL;
	}

	const uint8_t dac_id = atoi(cmd->argv[1]);

	if (dac_id != 1) {
		printf(CLI_DAC_INVALID_ID);
		return EINVAL;
	}

	const float dac_value_f = atof(cmd->argv[2]);

	// the value is 0 but the user entered a different value or is in invalid range
	if ((0 == dac_value_f && strcmp(cmd->argv[2], "0"))) {
		printf(CLI_DAC_INVALID_OPTION);
		return EINVAL;
	} else if (dac_value_f < 0 || dac_value_f > DAC_MAX_VALUE) {
		printf(CLI_DAC_INVALID_VALUE);
		return EINVAL;
	}

	const uint16_t dac_value = (dac_value_f * 4095);

	HAL_DAC_SetValue(cmd->bsp->hdacx, DAC_CHANNEL_2, DAC_ALIGN_12B_R, dac_value);
	printf("dac: write: success!\r\n");
	printf("output set to %d\r\n", dac_value);

	return 0;
}

