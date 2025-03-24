//
// Created by Artyom on 3/17/2025.
//
#include "cli.h"
#include <string.h>
#include <ctype.h>

void make_cli_engine(cli_engine_t *engine, UART_HandleTypeDef *huartx) {
	engine ->huartx = huartx;
	engine->prompt_trigger = 1;
	engine->pos = 0;
	engine->bsp = NULL;
	memset(engine->buf, 0, ENGINE_BUFFER_SIZE);

	for (uint16_t i = 0; i < UINT8_MAX; ++i) {
		if (isalnum(i) || i == ' ') {
			engine->handlers[i] = &handle_alnum;
		} else if (i == '\n') {
			engine->handlers[i] = &handle_nl;
		} else if (i == '\b') {
			engine->handlers[i] = &handle_bs;
		} else {
			engine->handlers[i] = &handle_no_op;
		}
	}
}

void cli_process(cli_engine_t *engine) {

  if (engine->prompt_trigger) {
	  engine->prompt_trigger = 0;
	  cli_writeline(engine->huartx, PROMPT);
  }

  if (HAL_OK == HAL_UART_Receive(engine->huartx, engine->buf + engine->pos, 1, UART_RECEIVE_TIMEOUT)) {
	  const uint8_t key = engine->buf[engine->pos];

	  // handling each key
	  engine->handlers[key](engine);
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

