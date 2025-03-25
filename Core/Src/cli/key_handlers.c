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
#include "../lexer/lexer.h"
#include "../utils/utils.h"

uint8_t handle_nl(cli_engine_t * const engine) {
	 engine->buf[engine->pos] = '\0';
//	 cli_putnl(engine->huartx);

	 HAL_UART_Transmit_IT(engine->huartx, "\r\n", 2);

	 bsp_exec(engine->bsp, (char *)engine->buf);

	 fflush(stdout);
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
//	cli_puts(engine->huartx, "\b");
//	cli_puts(engine->huartx, " ");
//	cli_puts(engine->huartx, "\b");

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

	HAL_UART_Transmit_IT(engine->huartx, engine->buf + engine->pos, 1);
	engine->pos += 1;

	return 0;
}
