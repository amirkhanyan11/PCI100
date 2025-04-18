/*
 * help.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */


#include "app.h"
#include <stdarg.h>
#include "cli_string_literals.h"
#include <errno.h>
#include "cli.h"

uint8_t cli_help(cmd_t * const cmd) {
	if (cmd->argc != 0) {
		printf("help: %s. Try `help` without options\r\n", CLI_INVALID_OPTIONS);
		return APP_INVALID_OPTIONS;
	}

	printf("\r\nAvailable commands:\r\n");

	printchunk("Led:", CLI_LED_HELP, NULL);

	printchunk("Eeprom:", CLI_EEPROM_HELP, NULL);

	printchunk("Pex:", CLI_PEX_HELP, NULL);

	printchunk("DAC:", CLI_DAC_HELP, NULL);

	printchunk("ADC:", CLI_ADC_HELP, NULL);

	return 0;
}
