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
#include "../utils/utils.h"

uint8_t exec_pex(cmd_t * const cmd) {

	const char * option = NULL;

	if (cmd->argc > 0) {
		option = cmd->argv[0];
	}

	uint8_t status = 0;

	if (!strcmp(option, "write")) {
		status = pex_write(cmd);
	} else if (!strcmp(option, "read")) {
		status = pex_read(cmd);
	} else if (NULL == option || !strcmp(option, "-h") || !strcmp(option, "--help")) {
		status = pex_help();
	} else {
		status = BSP_INVALID_OPTIONS;
	}

	if (BSP_INVALID_OPTIONS == status) {
		printf("pex: error: invalid option `%s`. See pex -h\r\n", option);
	}

	return status;
}

uint8_t pex_help(void) {
	printf(CLI_PEX_HELP);
	return 0;
}

uint8_t pex_write(cmd_t * const cmd) {

	if (cmd->argc != 3) {
		printf(CLI_INVALID_OPTIONS);
		return EINVAL;
	}

	uint32_t register_addr = strtol(cmd->argv[1], NULL, 16);

	if (!register_addr && strcmp(cmd->argv[1], "0")) {
		printf("pex: write: Invalid dev address format\r\n");
		return EINVAL;
	}

	const uint32_optional_t res = satoi(cmd->argv[2]);
	const uint32_t val = res.val;

	if (!res.has_val) {
		printf("pex: write: Invalid value\r\n");
		return EINVAL;
	}

	// the remaining 4 bytes of the payload are initialized with user input
	uint8_t payload[8] = { PEX_CB1_WRITE_REGISTER, PEX_CB2_TRANSPARENT_PORTS, PEX_CB3_ENABLE_ALL, register_addr };

	for (uint8_t i = 4, shift_offset = 24; i < 8; ++i, shift_offset -= 8) {
		payload[i] = (val >> shift_offset);
	}

	if (HAL_OK == HAL_I2C_Master_Transmit(cmd->bsp->hi2cx, PEX_SLAVE_ADDRESS, payload, sizeof(payload), HAL_MAX_DELAY)) {
		printf("pex: write: success!\r\n");
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

	uint32_t register_addr = strtol(cmd->argv[1], NULL, 16);

	if (!register_addr && strcmp(cmd->argv[1], "0")) {
		printf("pex: write: Invalid dev address format\r\n");
		return EINVAL;
	}

	uint8_t payload[] = { PEX_CB1_READ_REGISTER, PEX_CB2_TRANSPARENT_PORTS, PEX_CB3_ENABLE_ALL, register_addr };
	HAL_I2C_Master_Transmit(cmd->bsp->hi2cx, PEX_SLAVE_ADDRESS, payload, sizeof(payload), 1000);

	uint8_t RX_Buf[4] = {0};

	HAL_I2C_Master_Receive(cmd->bsp->hi2cx, PEX_SLAVE_ADDRESS, RX_Buf, sizeof(RX_Buf), 1000);
	printf("pex: read: success!\r\n");

	uint32_t res = 0;

	for (uint8_t i = 0; i < 4; ++i) {
		res = (res << 8) | RX_Buf[i];
	}

	printf("read value:\r\n");
	printf("decimal - %lu\r\n", res);
	printf("hex - %lX\r\n", res);


//	uint16_t deviceId = res[0];
//	deviceId <<= 8;
//	deviceId |= res[1];
//
//	uint16_t vendorId = res[2];
//	vendorId <<= 8;
//	vendorId |= res[3];
//
//
//	printf("Device ID: %u\r\n", deviceId);
//	printf("Vendor ID: %u\r\n", vendorId);


//
//	uint8_t payload[] = { register_addr, 0 };
//
//	if (HAL_OK == HAL_I2C_Master_Transmit(cmd->bsp->hi2cx, PEX_SLAVE_ADDRESS, payload, 2, 1000)) {
//		const uint8_t data = payload[1];
//		printf("pex: read: %d\r\n", data);
//	} else {
//		printf("pex: write: something went wrong\r\n");
//	}


	return 0;
}
