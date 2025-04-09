/*
 * cli_adc.c
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#include "app.h"
#include "cli_adc.h"
#include "adc.h"
#include <string.h>

uint8_t cli_adc(cmd_t * const cmd)
{
	const char * option = NULL;

	if (cmd->argc > 0) {
		option = cmd->argv[0];
	}

	uint8_t status = 0;

	if (NULL == option || !strcmp(option, "-h") || !strcmp(option, "--help")) {
		printchunk("Usage:", CLI_ADC_HELP, NULL);
	} else if (!strcmp(option, "read")) {
		status = start_chain(cmd, cli_adc_read_middleware, adc_read, NULL);
	} else {
		printf("adc: error: invalid option `%s`. See adc -h\r\n", option);
		status = APP_INVALID_OPTIONS;
	}

	return status;
}
