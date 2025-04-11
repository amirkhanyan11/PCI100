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

#define APP_COMMAND_NOT_FOUND 127
#define APP_LINE_TOO_LONG 139
#define APP_INVALID_OPTIONS 166

#define UART_RX_BUFFER_SIZE 1

struct cmd_config_s
{
	struct
	{
		char name[TOKEN_MAX_LENGTH];
		exec_t exec;
	}
	cmds[APP_MAX_CMDS];
	uint16_t length;
};

struct app_s
{
	cli_engine_t	engine;

	led_t			led;

	pci100_bsp_t	*bsp;

	cmd_config_t  	sc_arr;
};

uint8_t app_router(app_t * const app, char *input);
uint8_t app_init(app_t * const app);
uint8_t cli_help(cmd_t * const cmd);
void 	app_run(app_t * const app);

#endif /* SRC_APP_APP_H_ */
