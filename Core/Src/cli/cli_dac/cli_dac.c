/*
 * dac_router.c
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */

#include <cli_dac/cli_dac.h>
#include "chain.h"
#include "cli.h"
#include "dac.h"
#include <string.h>

uint8_t cli_dac(cmd_t * const cmd) {

	const char * option = NULL;

	if (cmd->argc > 0) {
		option = cmd->argv[0];
	}

	uint8_t status = 0;

	if (NULL == option || !strcmp(option, "-h") || !strcmp(option, "--help")) {
		printchunk("Usage:", CLI_DAC_HELP, NULL);
	} else if (!strcmp(option, "write")) {
		status = cli_dac_write_route(cmd);
	} else {
		printf("dac: error: invalid option `%s`. See dac -h\r\n", option);
		status = APP_INVALID_OPTIONS;
	}

	return status;
}
