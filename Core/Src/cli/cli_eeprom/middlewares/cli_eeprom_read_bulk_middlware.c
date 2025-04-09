/*
 * cli_eeprom_read_middlware.c
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#include "cli.h"
#include "bsp.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "chain.h"
#include "cli_eeprom.h"
#include "utils.h"
#include "cmd.h"


uint8_t cli_eeprom_read_bulk_middleware(cmd_t * const cmd, chain_t *const chain)
{

	if (cmd->argc != 3) {
		return __eeprom_err(cmd->argv[0], CLI_EEPROM_READ_BULK_HELP);
	}
	uint32_optional_t val_o = satoi(cmd->argv[1]);

	if (!val_o.has_val) {
		return __eeprom_err(cmd->argv[0], CLI_EEPROM_READ_BULK_HELP);
	}

	uint16_t address = val_o.val;

	val_o = satoi(cmd->argv[2]);

	if (!val_o.has_val || val_o.val == 0) {
		return __eeprom_err(cmd->argv[0], CLI_EEPROM_READ_BULK_HELP);
	}

    uint16_t size = val_o.val;

    const chain_fn_t next = chain_get_next(chain);

	if (!next) {
		printf("eeprom: read_bulk: something went wrong\r\n");
		return EINVAL;
	}

	uint8_t data[EEPROM_READ_MAX_SIZE] = {0};

	uint8_t status = next(cmd->app->bsp->hspix, address, size, data);

	if (status == HAL_OK) {
		printf("eeprom: read_bulk: success!\r\n");
		for (uint8_t i = 0; i < size; ++i) {
			printf(("data at %d address = %d\r\n"), address++, data[i]);
		}
	} else {
		printf("Error occurred during write process.\r\n");
	}

    return HAL_OK;
}
