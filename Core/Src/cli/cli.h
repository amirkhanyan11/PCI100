//
// Created by Artyom on 3/17/2025.
//

#ifndef CLI_H
#define CLI_H

#include "main.h"
#include "../filo/filo.h"
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

struct cli_engine_s
{
	uint8_t 	prompt_trigger;
	fifo_t		*uart_buffer;
	bsp_t		*bsp;

	filo_t		line;
};


void cli_poll(cli_engine_t *engine);
void cli_writeline(UART_HandleTypeDef *huartx, const char *s);
void cli_puts(UART_HandleTypeDef *huartx, const char *s);
void cli_putnl(UART_HandleTypeDef *huartx);
void engine_init(cli_engine_t *engine, fifo_t *fifo);


// handle keys
uint8_t handle_nl(cli_engine_t * const engine);
uint8_t handle_bs(cli_engine_t * const engine);

#endif //CLI_H
