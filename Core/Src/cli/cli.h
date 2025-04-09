//
// Created by Artyom on 3/17/2025.
//

#ifndef CLI_H
#define CLI_H

#include "main.h"
#include "filo.h"
#include <stdbool.h>
#include <stdio.h>
#include "typedefs.h"
#include "fifo.h"
#include "cli_string_literals.h"

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

#define UART_RECEIVE_TIMEOUT 100
#define UART_TRANSMIT_TIMEOUT 100

#define HISTORY_SIZE 32

struct history_s
{
	char		buffer[HISTORY_SIZE][FILO_BUFFER_SIZE];
	uint16_t	pivot;
	bool		shifted;
	uint16_t	pos;
};

void history_init(history_t * const history);
void history_set(history_t * const history, const char *str);
char *history_shift(history_t *const history);
char *history_unshift(history_t * const history);
void history_set_pivot(history_t * const history);
void history_reset_pos(history_t * const history);
bool history_can_shift(history_t * const history);


struct cli_engine_s
{
	app_t		*app;
	fifo_t		*buffer;
	filo_t		line;
	history_t	history;
};


void cli_poll(cli_engine_t *engine);
void cli_writeline(UART_HandleTypeDef *huartx, const char *s);
void cli_puts(UART_HandleTypeDef *huartx, const char *s);
void cli_putnl(UART_HandleTypeDef *huartx);
void engine_init(cli_engine_t *engine, app_t * const app, fifo_t *fifo, UART_HandleTypeDef * const huartx);
void cli_clear_output(cli_engine_t *engine);

void __attribute__((sentinel)) printchunk(const char *s, ...);

// handle keys
uint8_t handle_nl(cli_engine_t * const engine);
uint8_t handle_bs(cli_engine_t * const engine);
uint8_t handle_arrows(cli_engine_t * const engine);



// commands

uint8_t cli_dac(cmd_t * const cmd);

#endif //CLI_H
