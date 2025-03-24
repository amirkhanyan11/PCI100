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

uint8_t bsp_cmd_add(bsp_t * const bsp, const char *name, exec_t exec) {
	if (!bsp || !name || !exec) {
		return EINVAL;
	}

	if (bsp->cmds_length == BSP_MAX_CMDS || name > TOKEN_MAX_LENGTH) {
		return EINVAL;
	}

	strcpy(bsp->cmds[bsp->cmds_length].name, name);

	bsp->cmds[bsp->cmds_length].exec = exec;

	bsp->cmds_length += 1;

	return 0;
}


exec_t bsp_cmd_get(bsp_t * const bsp, const char *name) {
	if (!bsp || !name) {
		return EINVAL;
	}

	for (uint8_t i = 0; i < bsp->cmds_length; ++i) {
		if (!strcmp(bsp->cmds[i].name, name)) {
			return bsp->cmds[i].exec;
		}
	}

	return NULL;
}
