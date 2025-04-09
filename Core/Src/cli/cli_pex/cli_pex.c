/*
 * cli_pex.c
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */

#include "cli_pex.h"

uint8_t cli_pex(cmd_t * const cmd) {

	const char * option = NULL;

	if (cmd->argc > 0) {
		option = cmd->argv[0];
	}

	uint8_t status = 0;

	if (NULL == option || !strcmp(option, "-h") || !strcmp(option, "--help")) {
		printchunk("Usage:", CLI_PEX_HELP, NULL);
	}
	else if (!strcmp(option, "read")) {
		status = start_chain(cmd, cli_pex_read_middleware, pex_read, NULL);
	}
	else if (!strcmp(option, "write")) {
		status = start_chain(cmd, cli_pex_write_middleware, pex_write, NULL);
	}
	else {
		printf("pex: error: invalid option `%s`. See pex -h\r\n", option);
		status = APP_INVALID_OPTIONS;
	}

	return status;
}

