/*
 * pex.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */


#include "pex.h"
#include "cmd.h"
#include "cli_string_literals.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

static uint8_t __pex_err(const char * const cmd, const char * const option, const char * const s)
{
	printf("pex: %s: %s\r\n", cmd, option);
	printchunk("Usage:", s, NULL);
	return EINVAL;
}


uint8_t exec_pex(cmd_t * const cmd) {

	const char * option = NULL;

	if (cmd->argc > 0) {
		option = cmd->argv[0];
	}

	uint8_t status = 0;

	if (NULL == option || !strcmp(option, "-h") || !strcmp(option, "--help")) {
		printchunk("Usage:", CLI_PEX_HELP, NULL);
	} else if (!strcmp(option, "read")) {
		status = pex_read(cmd);
	} else if (!strcmp(option, "write")) {
		status = pex_write(cmd);
	} else {
		printf("pex: error: invalid option `%s`. See pex -h\r\n", option);
		status = APP_INVALID_OPTIONS;
	}

	return status;
}

uint8_t pex_write(cmd_t * const cmd) {

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

	// the remaining 4 bytes of the payload are initialized with user input
	uint8_t payload[8] = { PEX_CB1_WRITE_REGISTER, PEX_CB2_TRANSPARENT_PORTS, PEX_CB3_ENABLE_ALL, register_addr };

	for (uint8_t i = 4, shift_offset = 24; i < 8; ++i, shift_offset -= 8) {
		payload[i] = (val >> shift_offset);
	}

	if (HAL_OK == HAL_I2C_Master_Transmit(cmd->app->hi2cx, PEX_SLAVE_ADDRESS, payload, sizeof(payload), HAL_MAX_DELAY)) {
		printf("pex: write: success!\r\n");
	} else {
		printf("pex: write: something went wrong\r\n");
	}

	return 0;
}

uint8_t pex_read(cmd_t * const cmd) {

	if (cmd->argc != 2)
	{
		return __pex_err(cmd->argv[0], CLI_INVALID_OPTIONS, CLI_PEX_WRITE_HELP);
	}

	uint32_t register_addr = strtol(cmd->argv[1], NULL, 16);

	if (!register_addr && strcmp(cmd->argv[1], "0")) {
		return __pex_err(cmd->argv[0], CLI_PEX_INVALID_ADDRESS, CLI_PEX_WRITE_HELP);
	}

	uint8_t payload[] = { PEX_CB1_READ_REGISTER, PEX_CB2_TRANSPARENT_PORTS, PEX_CB3_ENABLE_ALL, register_addr };
	HAL_I2C_Master_Transmit(cmd->app->hi2cx, PEX_SLAVE_ADDRESS, payload, sizeof(payload), 1000);

	uint8_t RX_Buf[4] = {0};

	HAL_I2C_Master_Receive(cmd->app->hi2cx, PEX_SLAVE_ADDRESS, RX_Buf, sizeof(RX_Buf), 1000);
	printf("pex: read: success!\r\n");

	uint32_t res = 0;

	for (uint8_t i = 0; i < 4; ++i) {
		res = (res << 8) | RX_Buf[i];
	}

	printf("read value:\r\n");
	printf("decimal - %lu\r\n", res);
	printf("hex - %lX\r\n", res);

	return 0;
}
