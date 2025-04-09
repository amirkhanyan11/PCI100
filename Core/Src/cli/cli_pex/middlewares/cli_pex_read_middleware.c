/*
 * cli_pex_read_middleware.c
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */



#include "cmd.h"
#include "cli_string_literals.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "bsp.h"

uint8_t __pex_err(const char * const cmd, const char * const option, const char * const s)
{
	printf("pex: %s: %s\r\n", cmd, option);
	printchunk("Usage:", s, NULL);
	return EINVAL;
}


uint8_t cli_pex_read_middleware(cmd_t * const cmd, chain_t * const chain) {

	if (cmd->argc != 2)
	{
		return __pex_err(cmd->argv[0], CLI_INVALID_OPTIONS, CLI_PEX_WRITE_HELP);
	}

	uint32_t register_addr = strtol(cmd->argv[1], NULL, 16);

	if (!register_addr && strcmp(cmd->argv[1], "0")) {
		return __pex_err(cmd->argv[0], CLI_PEX_INVALID_ADDRESS, CLI_PEX_WRITE_HELP);
	}

	const chain_fn_t next = chain_get_next(chain);

	if (!next) {
		printf("pex: error: something went wrong\r\n");
	}

	const uint32_t res = next(cmd->app->bsp->hi2cx, register_addr);

	printf("read value:\r\n");
	printf("decimal - %lu\r\n", res);
	printf("hex - %lX\r\n", res);

	return 0;
}
