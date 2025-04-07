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

	const char * option = NULL;

	if (cmd->argc > 0) {
		option = cmd->argv[0];
	}

	uint8_t status = 0;

	if (!strcmp(option, "write")) {
		status = dac_write(cmd);
	} else if (NULL == option || !strcmp(option, "-h") || !strcmp(option, "--help")) {
		status = dac_help();
	} else {
		status = BSP_INVALID_OPTIONS;
	}

	if (BSP_INVALID_OPTIONS == status) {
		printf("dac: error: invalid option `%s`. See dac -h\r\n", option);
	}

	return status;
}

uint8_t dac_help(void) {
	printf(CLI_DAC_HELP);
	return 0;
}

uint8_t dac_write(cmd_t * const cmd) {

	if (cmd->argc != 3) {
		printf("dac: write: %s", CLI_INVALID_OPTIONS);
		return EINVAL;
	}

	const uint8_t dac_id = satoi(cmd->argv[1]).val;

	if (dac_id != 1) {
		printf(CLI_DAC_INVALID_ID);
		return EINVAL;
	}

	const double_optional_t res = satof(cmd->argv[2]);

	const double value = res.val;

	if (!res.has_val) {
		printf(CLI_DAC_INVALID_OPTION);
		return EINVAL;
	} else if (value < 0 || value > DAC_MAX_VALUE) {
		printf(CLI_DAC_INVALID_VALUE);
		return EINVAL;
	}

	const uint16_t dac_value = (value * 4095);

	HAL_DAC_SetValue(cmd->bsp->hdacx, DAC_CHANNEL_2, DAC_ALIGN_12B_R, dac_value);
	printf("dac: write: success!\r\n");
	printf("output set to %d\r\n", dac_value);

	return 0;
}

