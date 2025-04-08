//
// Created by Artyom on 3/17/2025.
//
#include "cli.h"
#include "cli_string_literals.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "fifo.h"
#include "bsp.h"
#include "typedefs.h"
#include <stdarg.h>

extern bsp_t bsp;

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(bsp.huartx, (uint8_t *)&ch, 1, UART_TRANSMIT_TIMEOUT);
  return ch;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1) {
		fifo_set(bsp.engine.uart_buffer, bsp.rx_buf[0]);
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_RxCpltCallback(huart);
}

void engine_init(cli_engine_t *engine, fifo_t *fifo) {
	engine->bsp = NULL;
	engine->uart_buffer = fifo;
	filo_init(&engine->line);
	history_init(&engine->history);
}

void cli_poll(cli_engine_t *engine) {
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
		else if (key == '\e')
		{
			HAL_Delay(1);
			handle_arrows(engine);
		}
		else if (isprint(key))
		{
			filo_set(&engine->line, key);
			HAL_UART_Transmit(engine->bsp->huartx, &key, 1, UART_TRANSMIT_TIMEOUT);
		}
	}
}

void cli_clear_output(cli_engine_t *engine) {
	while(!filo_is_empty(&engine->line)) {
		filo_get(&engine->line);
		cli_puts(engine->bsp->huartx, "\b \b");
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

void __attribute__((sentinel)) printchunk(const char *s, ...) {

	printf("\r\n");

	printf("%s\r\n", s);

	va_list list;
	va_start(list, s);

	const char *p = NULL;

	while ((p = va_arg(list, char *)) != NULL) {
		printf("  %s\r\n", p);
	}

	printf("\r\n");
}




