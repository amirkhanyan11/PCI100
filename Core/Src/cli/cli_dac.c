/*
 * cli_dac.c
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */

#include "dac.h"
#include "cli.h"
#include "bsp.h"
#include "cli_string_literals.h"
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

static uint8_t cli_dac_write(cmd_t * const cmd);

uint8_t cli_dac(cmd_t * const cmd) {

	const char * option = NULL;

	if (cmd->argc > 0) {
		option = cmd->argv[0];
	}

	uint8_t status = 0;

	if (NULL == option || !strcmp(option, "-h") || !strcmp(option, "--help")) {
		printchunk("Usage:", CLI_DAC_HELP, NULL);
	} else if (!strcmp(option, "write")) {
		status = cli_dac_write(cmd);
	} else {
		printf("dac: error: invalid option `%s`. See dac -h\r\n", option);
		status = APP_INVALID_OPTIONS;
	}

	return status;
}


static uint8_t cli_dac_write(cmd_t * const cmd) {

	if (cmd->argc != 3) {
		printf("dac: write: %s\r\n", CLI_INVALID_OPTIONS);
		printchunk("Usage:", CLI_DAC_HELP, NULL);
		return EINVAL;
	}

	const uint8_t dac_id = satoi(cmd->argv[1]).val;
	const double_optional_t res = satof(cmd->argv[2]);
	const double d_value = res.val;

	if (dac_id != 1 || !res.has_val || d_value < 0 || d_value > DAC_MAX_VALUE) {
		printf("dac: write: %s\r\n", CLI_INVALID_OPTIONS);
		printchunk("Usage:", CLI_DAC_HELP, NULL);
		return EINVAL;
	}

	const uint16_t value = d_value * 4095;

	dac_write(cmd->app->bsp->hdacx, DAC_CHANNEL_2, DAC_ALIGN_12B_R, value);

	printf("dac: write: success!\r\n");
	printf("output set to %d\r\n", value);

	return 0;
}
