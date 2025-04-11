/*
 * cli_eeprom.c
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#include "spi.h"
#include "app.h"
#include "cli.h"
#include "bsp.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "chain.h"
#include "cli_eeprom.h"
#include "utils.h"
#include "cmd.h"

uint8_t cli_eeprom(cmd_t * const cmd)
{
	const char * option = NULL;

	if (cmd->argc > 0) {
		option = cmd->argv[0];
	}

	uint8_t status = 0;

	if (!strcmp(option, "write")) {
		status = start_chain(cmd, cli_eeprom_write_middleware, spi_write, NULL);
	} else if (!strcmp(option, "read")) {
		status = start_chain(cmd, cli_eeprom_read_middleware, spi_read, NULL);
	} else if (!strcmp(option, "read_bulk")) {
		status = start_chain(cmd, cli_eeprom_read_bulk_middleware, spi_read_bulk, NULL);
	} else if (NULL == option || !strcmp(option, "-h") || !strcmp(option, "--help")) {
		printchunk("eeprom:", CLI_EEPROM_HELP, NULL);
	} else {
		printf("eeprom: error: invalid option `%s`. See eeprom -h\r\n", option);
		status = APP_INVALID_OPTIONS;
	}

	return status;
}


uint8_t cli_eeprom_write_middleware(cmd_t * const cmd, chain_t *const chain)
{

	if (cmd->argc != 3) {
		return __eeprom_err(cmd->argv[0], CLI_EEPROM_WRITE_HELP);
	}
	uint32_optional_t val_o = satoi(cmd->argv[1]);

	if (!val_o.has_val) {
		return __eeprom_err(cmd->argv[0], CLI_EEPROM_WRITE_HELP);
	}

	uint16_t address = val_o.val;

	val_o = satoi(cmd->argv[2]);

	if (!val_o.has_val) {
		return __eeprom_err(cmd->argv[0], CLI_EEPROM_WRITE_HELP);
	}

	uint8_t data = val_o.val;

    const chain_fn_t next = chain_get_next(chain);

	if (!next) {
		printf("eeprom: write: something went wrong\r\n");
		return EINVAL;
	}

	uint8_t status = next(cmd->app->bsp->hspix, address, data);

    if (status == HAL_OK) {
    	printf("eeprom: write: success!\r\n");
    	printf("data at %d address set to %d\r\n", address, data);
    } else {
    	printf("Error occurred during write process.\r\n");
    }
    return status;
}


uint8_t cli_eeprom_read_middleware(cmd_t * const cmd, chain_t *const chain)
{
	if (cmd->argc != 2) {
		return __eeprom_err(cmd->argv[0], CLI_EEPROM_READ_HELP);
	}
	uint32_optional_t val_o = satoi(cmd->argv[1]);

	if (!val_o.has_val) {
		return __eeprom_err(cmd->argv[0], CLI_EEPROM_READ_HELP);
	}

	uint16_t address = val_o.val;

	const chain_fn_t next = chain_get_next(chain);

	if (!next) {
		printf("eeprom: read: something went wrong\r\n");
		return EINVAL;
	}

	uint8_t data = 0;

    uint8_t status = next(cmd->app->bsp->hspix, address, &data);

    if (status == HAL_OK) {
    	printf("eeprom: read: success!\r\n");
    	printf("data at %d address = %d\r\n", address, data);
	} else {
		printf("Error occurred during write process.\r\n");
	}

    return status;
}


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

