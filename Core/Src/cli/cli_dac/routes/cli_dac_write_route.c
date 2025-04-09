/*
 * cli_dac_write_route.c
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */

#include <cli_dac/cli_dac.h>
#include "chain.h"
#include "cli.h"
#include "dac.h"

uint8_t cli_dac_write_route(cmd_t * const cmd) {

	chain_t chain = {0};
	chain_init(&chain);

	chain_add_many(&chain, cli_dac_write_controller, dac_write, NULL);


	const chain_fn_t next = chain_get_next(&chain);

	return next(cmd, &chain);
}
