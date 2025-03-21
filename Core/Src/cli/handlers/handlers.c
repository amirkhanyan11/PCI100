/*
 * handlers.c
 *
 *  Created on: Mar 21, 2025
 *      Author: artyom
 */

#include "handlers.h"
#include <string.h>

void engine_handle_nl(cli_engine_t * const engine) {

	// getting rig of the `\r` character before delegating command handling
	engine->buf[engine->pos] = '\0';

	cli_putnl(engine->huartx);

	// delegate command handling to the member handler
	engine->handle((const char *)engine->buf);

	// flush the buffer, reset the position
	memset(engine->buf, 0, UART_BUFFER_SIZE);
	engine->pos = 0;
	engine->prompt_trigger = 1;
}


void engine_handle_backspace(cli_engine_t * const engine) {
	if (!engine->pos) {
		return;
	}
	engine->buf[engine->pos] = '\0';
	engine->pos -= 1;
	HAL_UART_Transmit(engine->huartx, (const uint8_t *)"\b", 1, UART_TRANSMIT_TIMEOUT);
	HAL_UART_Transmit(engine->huartx, (const uint8_t *)" ", 1, UART_TRANSMIT_TIMEOUT);
	HAL_UART_Transmit(engine->huartx, (const uint8_t *)"\b", 1, UART_TRANSMIT_TIMEOUT);
}
