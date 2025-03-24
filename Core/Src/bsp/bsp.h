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
#include <stdio.h>

#define BSP_MAX_CMDS 128

struct bsp_cmd_s
{
	char name[TOKEN_MAX_LENGTH];
	exec_t exec;
};

struct bsp_s
{
	uint32_t blink_frequency;
	uint8_t blink_mode;
	uint8_t led_state;
	struct cli_engine_s *engine;
	bsp_cmd_t cmds[BSP_MAX_CMDS];
	DAC_HandleTypeDef *hdacx;
	uint8_t cmds_length;
};

uint8_t bsp_exec(bsp_t * const bsp, char *input);
uint8_t bsp_cmd_add(bsp_t * const bsp, const char *name, exec_t exec);
exec_t bsp_cmd_get(bsp_t * const bsp, const char *name);
void bsp_run(bsp_t * const bsp);
uint8_t make_bsp(bsp_t * const bsp, struct cli_engine_s * const engine, DAC_HandleTypeDef *hdacx);
void bsp_blink_led(bsp_t * const bsp);
uint8_t exec_help(cmd_t * const cmd);

#endif /* SRC_BSP_BSP_H_ */
