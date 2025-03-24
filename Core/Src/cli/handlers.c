/*
 * handlers.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#include "cli.h"
#include <errno.h>
#include <string.h>
#include "../cmd/cmd.h"

uint8_t handle_nl(cli_engine_t * const engine) {
	 engine->buf[engine->pos] = '\0';
	 cli_putnl(engine->huartx);

	 cmd_t cmd;
	 if (ESRCH == make_cmd(&cmd, engine->bsp, (char *)engine->buf)) {
		 cli_writeline(engine->huartx, "error: command not found");
	 } else {
		 cmd.exec(&cmd);
	 }


	 memset(engine->buf, 0, ENGINE_BUFFER_SIZE);
	 engine->pos = 0;
	 engine->prompt_trigger = 1;

	 return 0;
}

uint8_t handle_bs(cli_engine_t * const engine) {
	if (0 == engine->pos) {
		return EAGAIN;
	}
	engine->buf[engine->pos] = '\0';
	engine->pos -= 1;
	cli_writeline(engine->huartx, "\b");
	cli_writeline(engine->huartx, " ");
	cli_writeline(engine->huartx, "\b");

	return 0;
}

uint8_t handle_no_op(cli_engine_t * const engine) {
	return 0;
}

uint8_t handle_alnum(cli_engine_t * const engine) {
	if (engine->pos == ENGINE_BUFFER_SIZE - 1) {
		 memset(engine->buf, 0, ENGINE_BUFFER_SIZE);
		 engine->pos = 0;
		 return EAGAIN;
	}

	HAL_UART_Transmit(engine->huartx, engine->buf + engine->pos, 1, UART_TRANSMIT_TIMEOUT);
	engine->pos += 1;

	return 0;
}
