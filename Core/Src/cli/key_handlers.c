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
#include "../fifo/fifo.h"
#include <ctype.h>

uint8_t handle_nl(cli_engine_t * const engine) {

	cli_putnl(engine->bsp->huartx);

	bsp_exec(engine->bsp, engine->line.buffer);

	fflush(stdout);

	HAL_UART_Transmit(engine->bsp->huartx, (const uint8_t *)PROMPT, strlen(PROMPT), UART_TRANSMIT_TIMEOUT);

	filo_reset(&engine->line);

	fifo_reset(engine->uart_buffer);

	return 0;
}

uint8_t handle_bs(cli_engine_t * const engine) {

	if (filo_is_empty(&engine->line)) {
		return EAGAIN;
	}
	filo_get(&engine->line);
	cli_puts(engine->bsp->huartx, "\b \b");

	return 0;
}

