/*
 * bsp.h
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_


#include "main.h"
#include "../cli/cli.h"
#include "../cmd/cmd.h"
#include "typedefs.h"
#include "../lexer/lexer.h"

#define BSP_MAX_CMDS 128

struct bsp_cmd_s
{
	char name[TOKEN_MAX_LENGTH];
	exec_t exec;
};

struct bsp_s
{
	struct cli_engine_s *engine;
	bsp_cmd_t cmds[BSP_MAX_CMDS];
	uint8_t cmds_length;
};

uint8_t bsp_cmd_add(bsp_t * const bsp, const char *name, exec_t exec);
exec_t bsp_cmd_get(bsp_t * const bsp, const char *name);
void bsp_run(bsp_t * const bsp);
uint8_t make_bsp(bsp_t * const bsp, struct cli_engine_s * const engine);

#endif /* SRC_BSP_BSP_H_ */
