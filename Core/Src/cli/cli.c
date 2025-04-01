//
// Created by Artyom on 3/17/2025.
//
#include "cli.h"
#include "cli_string_literals.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../fifo/fifo.h"
#include "../bsp/bsp.h"
#include "typedefs.h"

void engine_init(cli_engine_t *engine, fifo_t *fifo) {
	engine->prompt_trigger = 1;
	engine->bsp = NULL;
	engine->uart_buffer = fifo;
	filo_init(&engine->line);
}

void cli_process(cli_engine_t *engine) {
	while(!fifo_is_empty(engine->uart_buffer)) {
		const uint8_t key = (uint8_t) fifo_get(engine->uart_buffer);
		if (key == '\r')
		{
			handle_nl(engine);
		}
		else if (key == '\b')
		{
			handle_bs(engine);
		}
		else if (isprint(key) || isspace(key))
		{
			filo_set(&engine->line, key);
			HAL_UART_Transmit_DMA(engine->bsp->huartx, &key, 1);
		}
	}
}

void cli_writeline(UART_HandleTypeDef *huartx, const char *s) {
  cli_puts(huartx, s);
  cli_putnl(huartx);
}

void cli_puts(UART_HandleTypeDef *huartx, const char *s) {
  HAL_UART_Transmit(huartx, (const uint8_t *)s, strlen(s), UART_TRANSMIT_TIMEOUT);
}

void cli_putnl(UART_HandleTypeDef *huartx) {
  HAL_UART_Transmit(huartx, (const uint8_t *)"\r\n", 2, UART_TRANSMIT_TIMEOUT);
}

