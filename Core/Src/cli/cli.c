//
// Created by Artyom on 3/17/2025.
//
#include "cli.h"
#include "cli_string_literals.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

void engine_init(cli_engine_t *engine, UART_HandleTypeDef *huartx) {
	engine ->huartx = huartx;
	engine->prompt_trigger = 1;
	engine->pos = 0;
	engine->bsp = NULL;
	memset(engine->buf, 0, ENGINE_BUFFER_SIZE);

	for (uint16_t i = 0; i < UINT8_MAX; ++i) {
		if (isalnum(i) || i == ' ') {
			engine->handlers[i] = &handle_alnum;
		} else {
			engine->handlers[i] = &handle_no_op;
		}
	}

	engine->handlers['\r'] = &handle_nl;
	engine->handlers['\b'] = &handle_bs;
}

void cli_process(cli_engine_t *engine) {

  if (engine->prompt_trigger) {
	  engine->prompt_trigger = 0;
	  printf(PROMPT);
  }

  if (HAL_OK == HAL_UART_Receive_IT(engine->huartx, engine->buf + engine->pos, 1)) {
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

