//
// Created by Artyom on 3/17/2025.
//

#ifndef CLI_H
#define CLI_H

#include "main.h"
#include "typedefs.h"


#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)


#define ENGINE_BUFFER_SIZE 1024
#define UART_RECEIVE_TIMEOUT 100
#define UART_TRANSMIT_TIMEOUT 100
#define CMD_MAX_LENGTH 128

#define PROMPT "PCI100$> "
#define CLI_WHITESPACE_DELIMITERS " \t"


// error codes
#define CLI_OK 0
#define CLI_ERROR 1
#define CLI_COMMAND_NOT_FOUND 127


struct cli_engine_s
{
	uint8_t prompt_trigger;
	UART_HandleTypeDef *huartx;
	uint32_t 	pos;
	uint8_t 	buf[ENGINE_BUFFER_SIZE];
	handle_key	handlers[UINT8_MAX];
	struct bsp_s		*bsp;
};


void cli_process(cli_engine_t *engine);
void cli_writeline(UART_HandleTypeDef *huartx, const char *s);
void cli_puts(UART_HandleTypeDef *huartx, const char *s);
void cli_putnl(UART_HandleTypeDef *huartx);
void make_cli_engine(cli_engine_t *engine, UART_HandleTypeDef *huartx);



// handle keys
uint8_t handle_nl(cli_engine_t * const engine);
uint8_t handle_bs(cli_engine_t * const engine);
uint8_t handle_no_op(cli_engine_t * const engine);
uint8_t handle_alnum(cli_engine_t * const engine);

#endif //CLI_H
