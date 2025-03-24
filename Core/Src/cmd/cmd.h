/*
 * cmd.h
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#ifndef SRC_CMD_CMD_H_
#define SRC_CMD_CMD_H_

#include "cli.h"

#define TOKEN_MAX_COUNT 16
#define TOKEN_MAX_LENGTH 32

typedef struct cmd_t;

typedef uint8_t (*exec_t)(cmd_t * const);

struct cmd_t
{
	char name[TOKEN_MAX_LENGTH];
	char args[TOKEN_MAX_COUNT - 1][TOKEN_MAX_LENGTH];
	exec_t exec;
};

uint8_t make_cmd(cmd_t * const cmd, char *input);

#endif /* SRC_CMD_CMD_H_ */
