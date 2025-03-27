/*
 * pex.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */


#include "pex.h"
#include "../cmd/cmd.h"
#include "../cli/cli_string_literals.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint8_t exec_pex(cmd_t * const cmd) {

	const char * const option = cmd->args[0];

	if (!strcmp(option, "write")) {
		return pex_write(cmd);
	}

	else if (!strcmp(option, "read")) {
		return pex_read(cmd);
	}

	printf("pex: "CLI_COMMAND_NOT_FOUND);
	return 127;
}

uint8_t pex_write(cmd_t * const cmd) {

	if (cmd->argc != 3) {
		printf(CLI_INVALID_OPTIONS);
		return EINVAL;
	}

	uint8_t register_addr = atoi(cmd->args[1]);

	if (!register_addr && strcmp(cmd->args[1], "0")) {
		printf("pex: write: Invalid dev address format\r\n");
		return EINVAL;
	}

	uint8_t val = atoi(cmd->args[2]);

	if (!val && strcmp(cmd->args[2], "0")) {
		printf("pex: write: Invalid value\r\n");
		return EINVAL;
	}

	uint8_t payload[]= { register_addr, val };

	if (HAL_OK == HAL_I2C_Master_Transmit(cmd->bsp->hi2cx, PEX_SLAVE_ADDRESS, payload, 2, 1000)) {
		printf("pex: write: OK!\r\n");
	} else {
		printf("pex: write: something went wrong\r\n");
	}

	return 0;
}

uint8_t pex_read(cmd_t * const cmd) {

	if (cmd->argc != 2) {
		printf(CLI_INVALID_OPTIONS);
		return EINVAL;
	}

	uint8_t register_addr = atoi(cmd->args[1]);

	if (!register_addr && strcmp(cmd->args[1], "0")) {
		printf("pex: write: Invalid dev address format\r\n");
		return EINVAL;
	}

	uint8_t payload[] = { register_addr, 0 };

	if (HAL_OK == HAL_I2C_Master_Transmit(cmd->bsp->hi2cx, PEX_SLAVE_ADDRESS, payload, 2, 1000)) {
		const uint8_t data = payload[1];
		printf("pex: read: %d\r\n", data);
	} else {
		printf("pex: write: something went wrong\r\n");
	}


	return 0;
}
