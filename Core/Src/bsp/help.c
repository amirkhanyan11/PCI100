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

	const char *messages[] = { CLI_PEX_HELP, CLI_LED_HELP, CLI_DAC_HELP, CLI_ADC_HELP, CLI_EEPROM_HELP };
	printf("\r\nAvailable commands:\r\n");

	for (uint8_t i = 0; i < sizeof(messages) / sizeof(messages[0]); ++i) {
		printf("%s", messages[i]);
	}

	return 0;
}
