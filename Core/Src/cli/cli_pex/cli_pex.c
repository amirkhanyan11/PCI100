/*
 * cli_pex.c
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */

#include "cli_pex.h"

uint8_t cli_pex(cmd_t * const cmd) {

	const char * option = NULL;

	if (cmd->argc > 0) {
		option = cmd->argv[0];
	}

	uint8_t status = 0;

	if (NULL == option || !strcmp(option, "-h") || !strcmp(option, "--help")) {
		printchunk("Usage:", CLI_PEX_HELP, NULL);
	}
	else if (!strcmp(option, "read")) {
		status = start_chain(cmd, cli_pex_read_middleware, pex_read, NULL);
	}
	else if (!strcmp(option, "write")) {
		status = start_chain(cmd, cli_pex_write_middleware, pex_write, NULL);
	}
	else {
		printf("pex: error: invalid option `%s`. See pex -h\r\n", option);
		status = APP_INVALID_OPTIONS;
	}

	return status;
}

uint8_t cli_pex_read_middleware(cmd_t * const cmd, chain_t *const chain) {

	if (cmd->argc != 2)
	{
		return __pex_err(cmd->argv[0], CLI_INVALID_OPTIONS, cli_get_help(cmd->name, cmd->argv[0]));
	}

	uint32_t register_addr = strtol(cmd->argv[1], NULL, 16);

	if (!register_addr && strcmp(cmd->argv[1], "0")) {
		return __pex_err(cmd->argv[0], CLI_PEX_INVALID_ADDRESS, cli_get_help(cmd->name, cmd->argv[0]));
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


uint8_t cli_pex_write_middleware(cmd_t * const cmd, chain_t *const chain) {

	if (cmd->argc != 3)
	{
		return __pex_err(cmd->argv[0], CLI_INVALID_OPTIONS, cli_get_help(cmd->name, cmd->argv[0]));
	}

	uint32_t register_addr = strtol(cmd->argv[1], NULL, 16);

	if (!register_addr && strcmp(cmd->argv[1], "0")) {
		return __pex_err(cmd->argv[0], CLI_PEX_INVALID_ADDRESS, cli_get_help(cmd->name, cmd->argv[0]));
	}

	const uint32_optional_t res = satoi(cmd->argv[2]);
	const uint32_t val = res.val;

	if (!res.has_val) {
		return __pex_err(cmd->argv[0], "Invalid value", cli_get_help(cmd->name, cmd->argv[0]));

	}

	const chain_fn_t next = chain_get_next(chain);

	if (!next) {
		printf("pex: error: something went wrong\r\n");
	}

	const uint8_t status = next(cmd->app->bsp->hi2cx, register_addr, val);

	if (HAL_OK == status) {
		printf("pex: write: success!\r\n");
	} else {
		printf("pex: write: something went wrong\r\n");
	}

	return status;
}

