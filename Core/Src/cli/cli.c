//
// Created by Artyom on 3/17/2025.
//
#include "cli.h"
#include "cli_string_literals.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "fifo.h"
#include "app.h"
#include "bsp.h"
#include "uart.h"

#include <stdarg.h>

void engine_init(cli_engine_t *engine, app_t * const app, fifo_t *fifo, uint8_t huartx) {
	engine->app = app;
	engine->buffer = fifo;
	filo_init(&engine->line);
	history_init(&engine->history);

	start_uart_receive_dma(huartx);
}

void cli_poll(cli_engine_t *engine) {
	while(!fifo_is_empty(engine->buffer)) {
		const uint8_t key = (uint8_t) fifo_get(engine->buffer);
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
			uart_transmit(engine->app->bsp->huartx, &key, 1);
		}
	}
}

void cli_clear_output(cli_engine_t *engine) {
	while(!filo_is_empty(&engine->line)) {
		filo_get(&engine->line);
		cli_puts(engine->app->bsp->huartx, "\b \b");
	}
}

void cli_writeline(uint8_t huartx, const char *s) {
  cli_puts(huartx, s);
  cli_putnl(huartx);
}

void cli_puts(uint8_t huartx, const char *s) {
	uart_transmit(huartx, (const uint8_t *)s, strlen(s));

}

void cli_putnl(uint8_t huartx) {
	uart_transmit(huartx, (const uint8_t *)"\r\n", 2);
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




