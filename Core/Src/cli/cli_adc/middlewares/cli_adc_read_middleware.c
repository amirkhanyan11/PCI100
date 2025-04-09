/*
 * cli_adc_read_middleware.c
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#include "cli_adc.h"
#include "cli.h"
#include "bsp.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "chain.h"
#include "utils.h"
#include "cmd.h"

uint8_t cli_adc_read_middleware(cmd_t * const cmd, chain_t *const chain)
{

	if (cmd->argc != 2) {
		return __adc_err();
	}
	uint32_optional_t channel = satoi(cmd->argv[1]);

	if (!channel.has_val || !adc_supported_channel(channel.val)) {
		return __adc_err();
	}

	float data;

	const chain_fn_t next = chain_get_next(chain);

	if (!next) {
		printf("adc: read: something went wrong\r\n");
		return EINVAL;
	}

	uint8_t status = next(cmd->app->bsp->hadcx, channel.val, &data);

	if (status == HAL_OK) {
		printf("adc: read: success!\r\n");
		printf("adc conversion = %.2fV\r\n", data);
	} else {
		printf("Error occurred during read process.\r\n");
	}

	return status;
}

