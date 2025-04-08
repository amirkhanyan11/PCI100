/*
 * cmd.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#include "cmd.h"
#include "app.h"
#include "led.h"
#include "lexer.h"
#include <string.h>
#include <errno.h>

static uint8_t bind_exec(cmd_t * const cmd) {

	exec_t e = app_cmd_get(cmd->app, cmd->name);

	if (NULL == e) {
		return ESRCH;
	}

	cmd->exec = e;

	return 0;
}

/*
 * cmd - pointer to already allocated command structure
 * input - user input string
 * */
uint8_t make_cmd(cmd_t * const cmd, app_t * const app, char *input) {
	if (!cmd || !input) {
		return EINVAL;
	}

	memset(cmd, 0, sizeof(cmd_t));

	cmd->app = app;

	const uint8_t parse_status = parse(cmd, input);

	if (parse_status) {
		return parse_status;
	}

	const uint8_t bind_exec_status = bind_exec(cmd);

	return bind_exec_status;
}




