//
// Created by Artyom on 3/17/2025.
//

#ifndef CLI_H
#define CLI_H

//#include "history.h"
#include "main.h"
#include "../filo/filo.h"
#include <stdbool.h>
#include "typedefs.h"


#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)


#define ENGINE_BUFFER_SIZE 1024
#define UART_RECEIVE_TIMEOUT 100
#define UART_TRANSMIT_TIMEOUT 100
#define CMD_MAX_LENGTH 128

#define PROMPT "Tyom@PCI100$> "
#define CLI_WHITESPACE_DELIMITERS " \t"

// error codes
#define CLI_OK 0
#define CLI_ERROR 1

#define HISTORY_SIZE 4

struct history_s
{
	char		buffer[HISTORY_SIZE][FILO_BUFFER_SIZE];
	uint16_t	pivot;
	bool		pivot_passed_shift;
	bool		pivot_passed_unshift;
	uint16_t	pos;
};

void history_init(history_t * const history);
void history_set(history_t * const history, const char *str);
char *history_shift(history_t *const history);
char *history_unshift(history_t * const history);
void history_roll(history_t * const history);


struct cli_engine_s
{
	bsp_t		*bsp;
	fifo_t		*uart_buffer;
	filo_t		line;
	history_t	history;
};


void cli_poll(cli_engine_t *engine);
void cli_writeline(UART_HandleTypeDef *huartx, const char *s);
void cli_puts(UART_HandleTypeDef *huartx, const char *s);
void cli_putnl(UART_HandleTypeDef *huartx);
void engine_init(cli_engine_t *engine, fifo_t *fifo);
void cli_clear_output(cli_engine_t *engine);


// handle keys
uint8_t handle_nl(cli_engine_t * const engine);
uint8_t handle_bs(cli_engine_t * const engine);
uint8_t handle_esc(cli_engine_t * const engine);

#endif //CLI_H
