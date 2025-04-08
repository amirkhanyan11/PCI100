/*
 * help.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */


#include "bsp.h"
#include <stdarg.h>
#include "cli_string_literals.h"
#include <errno.h>
#include "cli.h"

uint8_t exec_help(cmd_t * const cmd) {
	if (cmd->argc != 0) {
		printf("help: %s", CLI_INVALID_OPTIONS);
		return BSP_INVALID_OPTIONS;
	}

	printf("\r\nAvailable commands:\r\n");

	printchunk("Led:", CLI_LED_HELP, NULL);

	printchunk("Eeprom:", CLI_EEPROM_HELP, NULL);

	printchunk("Pex:", CLI_PEX_HELP, NULL);

	printchunk("DAC:", CLI_DAC_HELP, NULL);

	printchunk("ADC:", CLI_ADC_HELP, NULL);

	return 0;
}
