/*
 * handlers.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#include "cli.h"

uint8_t handle_nl(cli_engine_t * const engine) {
	 engine->buf[engine->pos] = '\0';
	 cli_putnl(huartx);
	 memset(engine->buf, 0, ENGINE_BUFFER_SIZE);
	 engine->pos = 0;
	 engine->prompt_trigger = 1;

	 return 0;
}

uint8_t handle_bs(cli_engine_t * const engine) {
	if (0 == engine->pos) {
		return;
	}
	engine->buf[engine->pos] = '\0';
	engine->pos -= 1;
	cli_writeline(engine->huartx, (const uint8_t *)"\b");
	cli_writeline(engine->huartx, (const uint8_t *)" ");
	cli_writeline(engine->huartx, (const uint8_t *)"\b");

	return 0;
}

uint8_t handle_no_op(cli_engine_t * const engine) {
	return 0;
}

uint8_t handle_alnum(cli_engine_t * const engine) {
	if (engine->pos == ENGINE_BUFFER_SIZE - 1) {
		 memset(engine->buf, 0, ENGINE_BUFFER_SIZE);
		 engine->pos = 0;
		 return 1;
	}

	HAL_UART_Transmit(engine->huartx, buf + pos, 1, UART_TRANSMIT_TIMEOUT);
	engine->pos += 1;

	return 0;
}
