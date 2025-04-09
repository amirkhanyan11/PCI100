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
#include <stdarg.h>
#include "chain.h"

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

uint8_t __attribute__((sentinel)) start_chain(cmd_t * const cmd, chain_fn_t first, ...) {

	chain_t chain = {0};
	chain_init(&chain);

	va_list list;
	va_start(list, first);

	if (-1 == chain_add(&chain, first)) {
		return -1;
	}

	chain_fn_t f = NULL;

	while ((f = va_arg(list, chain_fn_t)) != NULL) {
		if (-1 == chain_add(&chain, f)) {
			return -1;
		}
	}

	const chain_fn_t next = chain_get_next(&chain);

	return next(cmd, &chain);
}




