/*
 * cli_dac.c
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */

#include "cli_dac.h"
#include "dac.h"
#include "cli.h"
#include "cli_string_literals.h"
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "chain.h"

#include "../../../../../BSP/PCI100/bsp.h"

uint8_t cli_dac_write_middleware(cmd_t * const cmd, chain_t *const chain) {

	if (cmd->argc != 3) {
		printf("dac: write: %s\r\n", CLI_INVALID_OPTIONS);
		printchunk("Usage:", CLI_DAC_HELP, NULL);
		return EINVAL;
	}

	const uint8_t dac_id = satoi(cmd->argv[1]).val;
	const double_optional_t res = satof(cmd->argv[2]);
	const double d_value = res.val;

	if (!dac_supported_channel(dac_id) || !res.has_val || d_value < 0 || d_value > DAC_MAX_VALUE) {
		printf("dac: write: %s\r\n", CLI_INVALID_OPTIONS);
		printchunk("Usage:", CLI_DAC_HELP, NULL);
		return EINVAL;
	}

	const uint16_t value = d_value * 4095;

	const chain_fn_t next = chain_get_next(chain);

	if (!next) {
		printf("dac: write: something went wrong\r\n");
		return EINVAL;
	}

	next(cmd->app->bsp->hdacx, DAC_CHANNEL_2, DAC_ALIGN_12B_R, value);

	printf("dac: write: success!\r\n");
	printf("output set to %d\r\n", value);

	return 0;
}

