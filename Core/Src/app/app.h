/*
 * app.h
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#ifndef SRC_APP_APP_H_
#define SRC_APP_APP_H_


#include "main.h"
#include "cli.h"
#include "cmd.h"
#include "typedefs.h"
#include "lexer.h"
#include <stdio.h>
#include "led.h"

#define APP_MAX_CMDS 128
#define UART_RX_BUFFER_SIZE 1

#define APP_COMMAND_NOT_FOUND 127
#define APP_LINE_TOO_LONG 139
#define APP_INVALID_OPTIONS 166

struct app_supported_cmds_s
{
	struct
	{
		char name[TOKEN_MAX_LENGTH];
		exec_t exec;
	} cmds[APP_MAX_CMDS];

	uint16_t length;
};

struct app_s
{
	uint8_t				 rx_buf[UART_RX_BUFFER_SIZE];
	cli_engine_t		 engine;

	struct led_s		 led;

	bsp_t				 *bsp;

	app_supported_cmds_t sc_arr;
};

uint8_t app_exec(app_t * const app, char *input);
uint8_t app_cmd_add(app_t * const app, const char *name, exec_t exec);
exec_t 	app_cmd_get(app_t * const app, const char *name);
void 	app_run(app_t * const app);
uint8_t app_init(app_t * const app, bsp_t * const bsp);
uint8_t exec_help(cmd_t * const cmd);

#endif /* SRC_APP_APP_H_ */
