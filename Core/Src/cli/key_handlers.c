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
#include "../cli/cli_string_literals.h"
#include <ctype.h>

uint8_t handle_nl(cli_engine_t * const engine) {

	cli_putnl(engine->bsp->huartx);

	char line[FILO_BUFFER_SIZE] = {0};
	strcpy(line, engine->line.buffer);

	const uint8_t status = bsp_exec(engine->bsp, line);

	/* At least the name of the command is correct
	 **/
	if (BSP_LINE_TOO_LONG != status && BSP_COMMAND_NOT_FOUND != status) {
		history_set(&engine->history, engine->line.buffer);
	}

	printf(PROMPT);

	fflush(stdout);

	filo_reset(&engine->line);

	fifo_reset(engine->uart_buffer);

	history_set_pivot(&engine->history);

	return 0;
}

uint8_t handle_bs(cli_engine_t * const engine) {

	if (filo_is_empty(&engine->line)) {
		return EAGAIN;
	}
	history_reset_pos(&engine->history);
	filo_get(&engine->line);
	cli_puts(engine->bsp->huartx, "\b \b");

	return 0;
}

uint8_t handle_arrows(cli_engine_t * const engine) {

	char next = fifo_get(engine->uart_buffer);
	if (next != '[') {
		if (next != -1) {
			fifo_unshift(engine->uart_buffer);
		}
		return -1;
	}

	next = fifo_get(engine->uart_buffer);

	if (!(next == 'A' && history_can_shift(&engine->history)) && next != 'B') {
		return -1;
	}

	cli_clear_output(engine);
	filo_reset(&engine->line);

	char *s = (next == 'A') ? history_shift(&engine->history) : history_unshift(&engine->history);

	if (!s) {
		return -1;
	}

	filo_set_many(&engine->line, s);

	printf("%s", s);
	fflush(stdout);


	return 0;
}





