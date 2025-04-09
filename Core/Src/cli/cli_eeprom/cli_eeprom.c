/*
 * cli_eeprom.c
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#include "cli_eeprom.h"
#include "app.h"
#include <string.h>

uint8_t cli_eeprom(cmd_t * const cmd)
{
	const char * option = NULL;

	if (cmd->argc > 0) {
		option = cmd->argv[0];
	}

	uint8_t status = 0;

	if (!strcmp(option, "write")) {
		status = cli_eeprom_write_route(cmd);
	} else if (!strcmp(option, "read")) {
		status = cli_eeprom_read_route(cmd);
	} else if (!strcmp(option, "read_bulk")) {
		status = cli_eeprom_read_bulk_route(cmd);
	} else if (NULL == option || !strcmp(option, "-h") || !strcmp(option, "--help")) {
		printchunk("eeprom:", CLI_EEPROM_HELP, NULL);
	} else {
		printf("eeprom: error: invalid option `%s`. See eeprom -h\r\n", option);
		status = APP_INVALID_OPTIONS;
	}

	return status;
}
