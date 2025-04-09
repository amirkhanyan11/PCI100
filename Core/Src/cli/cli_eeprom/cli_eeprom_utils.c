/*
 * cli_eeprom_utils.c
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */


#include "cli_eeprom.h"
#include <errno.h>

uint8_t __eeprom_err(const char * const cmd, const char * const s)
{
	printf("eeprom: %s: %s\r\n", cmd, CLI_INVALID_OPTIONS);
	printchunk("Usage:", s, NULL);
	return EINVAL;
}
