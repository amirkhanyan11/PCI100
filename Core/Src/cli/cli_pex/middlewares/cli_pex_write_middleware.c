
#include "cli_pex.h"

uint8_t cli_pex_write_middleware(cmd_t * const cmd, chain_t *const chain) {

	if (cmd->argc != 3)
	{
		return __pex_err(cmd->argv[0], CLI_INVALID_OPTIONS, CLI_PEX_WRITE_HELP);
	}

	uint32_t register_addr = strtol(cmd->argv[1], NULL, 16);

	if (!register_addr && strcmp(cmd->argv[1], "0")) {
		return __pex_err(cmd->argv[0], CLI_PEX_INVALID_ADDRESS, CLI_PEX_WRITE_HELP);
	}

	const uint32_optional_t res = satoi(cmd->argv[2]);
	const uint32_t val = res.val;

	if (!res.has_val) {
		return __pex_err(cmd->argv[0], "Invalid value", CLI_PEX_WRITE_HELP);

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
