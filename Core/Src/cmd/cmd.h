/*
 * cmd.h
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#ifndef SRC_CMD_CMD_H_
#define SRC_CMD_CMD_H_

#include "main.h"
#include "../bsp/bsp.h"
#include "../lexer/lexer.h"
#include "typedefs.h"

struct cmd_s
{
	char name[TOKEN_MAX_LENGTH];
	bsp_t *bsp;
	char args[ARG_MAX_COUNT][TOKEN_MAX_LENGTH];
	uint8_t argc;
	exec_t exec;
};

uint8_t make_cmd(cmd_t * const cmd, bsp_t * const bsp, char *input);

#endif /* SRC_CMD_CMD_H_ */
