/*
 * cli_eeprom_read_bulk_route.c
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#include "cli_eeprom.h"
#include "chain.h"
#include "cli.h"
#include "spi.h"

uint8_t cli_eeprom_read_bulk_route(cmd_t * const cmd) {

	chain_t chain = {0};
	chain_init(&chain);

	chain_add_many(&chain, cli_eeprom_read_bulk_middleware, spi_write, NULL);


	const chain_fn_t next = chain_get_next(&chain);

	return next(cmd, &chain);
}

