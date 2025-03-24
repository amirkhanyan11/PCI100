/*
 * cmd.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#include "cmd.h"
#include "../led/led.h"
#include "../lexer/lexer.h"
#include <string.h>

static uint8_t bind_exec(cmd_t * const cmd) {
	exec_t e = bsp_cmd_get(name);

	if (NULL == e) {
		return EINVAL;
	}

	cmd->exec = exec;

	return 0;
}


/*
 * cmd - pointer to already allocated command structure
 * input - user input string
 * */
uint8_t make_cmd(cmd_t * const cmd, char *input) {
	if (!cmd || !input) {
		return EINVAL;
	}

	memset(cmd, 0, sizeof(cmd_t));

	const uint8_t parse_status = parse(cmd, input);

	if (parse_status) {
		return parse_status;
	}

	const uint8_t bind_exec_status = bind_exec_status(cmd);

	switch (bind_exec_status)
	{
	case EINVAL:
		// printf cmd not found
	default:
		return bind_exec_status;
	}

	return 0;
}
