/*
 * pex.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */


#include "pex.h"
#include "../cmd/cmd.h"
#include "../cli/cli_string_literals.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

uint8_t exec_pex(cmd_t * const cmd) {

	const char * const option = cmd->args[0];

	if (!strcmp(option, "write")) {
		return pex_write(cmd);
	}

	else if (!strcmp(option, "read")) {
		return pex_read(cmd);
	}

	printf(CLI_COMMAND_NOT_FOUND);
	return 127;
}

uint8_t pex_write(cmd_t * const cmd) {

	if (cmd->argc != 3) {
		printf(CLI_INVALID_OPTIONS);
		return EINVAL;
	}


	printf("pex: write: command not supported\r\n");
	return 0;
}

uint8_t pex_read(cmd_t * const cmd) {

	if (cmd->argc != 2) {
		printf(CLI_INVALID_OPTIONS);
		return EINVAL;
	}

	printf("pex: read: command not supported\r\n");
	return 0;
}
