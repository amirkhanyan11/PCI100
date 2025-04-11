/*
 * app.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#include <errno.h>
#include "app.h"
#include "string.h"
#include "fifo.h"
#include "cmd.h"
#include "utils.h"
#include "cli_string_literals.h"

#include "bsp.h"

extern fifo_t UART_FIFO1;

void app_run(app_t * const app) {

	led_blink(&app->led);

	cli_poll(&app->engine);
}

uint8_t app_router(app_t * const app, char *line) {
	strtrim(line, WHITESPACE);

	const uint16_t line_length = strlen(line);
	if (line_length == 0) {
		return APP_COMMAND_NOT_FOUND;
	} else if (line_length >= FILO_BUFFER_SIZE) {
		printf("error: line too long\r\n");
		return APP_LINE_TOO_LONG;
	}

	cmd_t cmd;
	const uint8_t status = make_cmd(&cmd, app, line);
	if (ESRCH == status) {
		printf("error: command not found\r\n");
		return APP_COMMAND_NOT_FOUND;
	} else if (E2BIG == status) {
		printf("error: token too large\r\n");
		return APP_LINE_TOO_LONG;
	}

	return cmd.exec(&cmd);
}

uint8_t app_init(app_t * const app) {
	app->sc_arr.length = 0;

	app->bsp = bsp_get();

	engine_init(&app->engine, app, &UART_FIFO1, app->bsp->huartx);

	fifo_init(&UART_FIFO1);

	led_init(&app->led);

	cli_config(app);

	printf("\r\n%s", PROMPT);
	fflush(stdout);

	return 0;
}
