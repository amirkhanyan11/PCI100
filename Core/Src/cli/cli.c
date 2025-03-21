//
// Created by Artyom on 3/17/2025.
//
#include "cli.h"
#include <string.h>
#include "../bsp/handlers/handlers.h"


void make_cli_engine(cli_engine_t *engine, UART_HandleTypeDef *huartx, message_handler_t handle) {


	engine->handle = handle;
	engine ->huartx = huartx;
	engine->prompt_trigger = 1;
	engine->pos = 0;
	memset(engine->buf, 0, CLI_BUFFER_SIZE);
}


void cli_process(cli_engine_t *engine) {

  if (engine->prompt_trigger) {
	  engine->prompt_trigger = 0;
	  cli_writeline(engine->huartx, PROMPT);
  }

  if (HAL_OK == HAL_UART_Receive(engine->huartx, engine->buf + engine->pos, 1, UART_RECEIVE_TIMEOUT)) {
    if (engine->buf[engine->pos] == '\r') {
    	engine_handle_nl(engine);
    }

    else if (engine->buf[engine->pos] == '\b') {
    	engine_handle_backspace(engine);
    }

    else {
      HAL_UART_Transmit(engine->huartx, engine->buf + engine->pos, 1, UART_TRANSMIT_TIMEOUT);
      engine->pos += 1;
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

