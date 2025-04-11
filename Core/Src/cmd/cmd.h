/*
 * cmd.h
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#ifndef SRC_CMD_CMD_H_
#define SRC_CMD_CMD_H_

#include "main.h"
#include "app.h"
#include "cli.h"
#include "lexer.h"
#include "typedefs.h"
#include "chain/chain.h"

struct cmd_s
{
	char name[TOKEN_MAX_LENGTH];
	app_t *app;
	char argv[ARG_MAX_COUNT][TOKEN_MAX_LENGTH];
	uint8_t argc;
	exec_t exec;
	const char **help;
};

uint8_t make_cmd(cmd_t * const cmd, app_t * const app, char *input);
uint8_t __attribute__((sentinel)) start_chain(cmd_t * const cmd, chain_fn_t first, ...);

#endif /* SRC_CMD_CMD_H_ */
