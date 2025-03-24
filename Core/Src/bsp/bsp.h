/*
 * bsp.h
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_


#include "main.h"
#include "../cmd/cmd.h"

#define BSP_MAX_CMDS 128

typedef struct
{
	char name[TOKEN_MAX_LENGTH];
	exec_t exec;
} bsp_cmd_t;


typedef struct
{
	cli_engine_t engine;
	bsp_cmd_t cmds[BSP_MAX_CMDS];
	uint8_t cmds_length;
} bsp_t;

uint8_t bsp_cmd_add(bsp_t * const bsp, const char *name, exec_t exec);
exec_t bsp_cmd_get(bsp_t * const bsp, const char *name);
void bsp_run(void);

#endif /* SRC_BSP_BSP_H_ */
