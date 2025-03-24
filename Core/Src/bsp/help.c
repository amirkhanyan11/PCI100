/*
 * help.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */


#include "bsp.h"
#include <errno.h>

uint8_t exec_help(cmd_t * const cmd) {
	if (cmd->argc != 0) {
		cli_writeline(cmd->bsp->engine->huartx, "help: error: invalid options");
		return EINVAL;
	}

//	cli_writeline(cmd->bsp->engine->huartx, "jan axpers");
	printf("jan axpers\r\n");

	return 0;
}
