//
// Created by Artyom on 3/17/2025.
//
#include "cli.h"
#include <string.h>


//static void cli_handlers(uint8_t * const buf, uint32_t * const pos, const uint8_t c) {
//	switch(c) {
//	case '\r':
//
//	}
//}


cli_engine_t make_cli_engine(UART_HandleTypeDef *huartx, message_handler_t handle) {

	cli_engine_t engine = {
			.handle = handle,
			.huartx = huartx,
			.buf = {0},
			.pos = 0
	};

	return engine;
}


void cli_process(cli_engine_t *engine) {

  static uint8_t prompt = 1;

  if (prompt) {
	  prompt = 0;
	  HAL_UART_Transmit(engine->huartx, (uint8_t *)PROMPT, 9, 100);
  }

  if (HAL_OK == HAL_UART_Receive(engine->huartx, engine->buf + engine->pos, 1, UART_RECEIVE_TIMEOUT)) {
    if (engine->buf[engine->pos] == '\r') {
      engine->buf[engine->pos] = '\0';
      cli_putnl(engine->huartx);
      engine->handle((const char *)engine->buf);
      memset(engine->buf, 0, UART_BUFFER_SIZE);
      engine->pos = 0;
      prompt = 1;
    }

    else if (engine->buf[engine->pos] == '\b') {
    	if (!engine->pos) {
    		return;
    	}
    	engine->buf[engine->pos] = '\0';
    	--(engine->pos);
    	HAL_UART_Transmit(engine->huartx, (const uint8_t *)"\b", 1, UART_TRANSMIT_TIMEOUT);
    	HAL_UART_Transmit(engine->huartx, (const uint8_t *)" ", 1, UART_TRANSMIT_TIMEOUT);
    	HAL_UART_Transmit(engine->huartx, (const uint8_t *)"\b", 1, UART_TRANSMIT_TIMEOUT);
    }

    else {
      HAL_UART_Transmit(engine->huartx, engine->buf + engine->pos, 1, UART_TRANSMIT_TIMEOUT);
      ++(engine->pos);
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

