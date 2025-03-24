/*
 * bsp.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#include "bsp.h"
#include "string.h"
#include <errno.h>
#include "../cmd/cmd.h"
#include "../led/led.h"
#include "../dac/dac.h"

void bsp_run(bsp_t * const bsp) {
	cli_process(bsp->engine);
}

uint8_t make_bsp(bsp_t * const bsp, struct cli_engine_s * const engine) {
	  bsp_cmd_add(bsp, "led", &exec_led);
	  bsp_cmd_add(bsp, "dac", &exec_dac);

	  bsp->engine = engine;
	  bsp->engine->bsp = bsp;

	  return 0;
}

uint8_t bsp_cmd_add(bsp_t * const bsp, const char *name, exec_t exec) {
	if (!bsp || !name || !exec) {
		return EINVAL;
	}

	if (bsp->cmds_length == BSP_MAX_CMDS || strlen(name) > TOKEN_MAX_LENGTH) {
		return EINVAL;
	}

	strcpy(bsp->cmds[bsp->cmds_length].name, name);

	bsp->cmds[bsp->cmds_length].exec = exec;

	bsp->cmds_length += 1;

	return 0;
}


exec_t bsp_cmd_get(bsp_t * const bsp, const char *name) {
	if (!bsp || !name) {
		return NULL;
	}

	for (uint8_t i = 0; i < bsp->cmds_length; ++i) {
		if (!strcmp(bsp->cmds[i].name, name)) {
			return bsp->cmds[i].exec;
		}
	}

	return NULL;
}
