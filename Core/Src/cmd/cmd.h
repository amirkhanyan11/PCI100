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

typedef uint8_t (*exec_t)(cmd_t * const);

typedef struct
{
	char name[TOKEN_MAX_LENGTH];
	char args[TOKEN_MAX_COUNT - 1][TOKEN_MAX_LENGTH];
	exec_t exec;
} cmd_t;

uint8_t make_cmd(cmd_t * const cmd, char *input);

#endif /* SRC_CMD_CMD_H_ */
