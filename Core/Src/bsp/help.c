/*
 * help.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */


#include "bsp.h"
#include "../cli/cli_string_literals.h"
#include <errno.h>

uint8_t exec_help(cmd_t * const cmd) {
	if (cmd->argc != 0) {
		printf("help: %s", CLI_INVALID_OPTIONS);
		return BSP_INVALID_OPTIONS;
	}
	printf("\r\nAvailable commands:\r\n%s%s%s", CLI_PEX_HELP, CLI_LED_HELP, CLI_DAC_HELP);

	return 0;
}
