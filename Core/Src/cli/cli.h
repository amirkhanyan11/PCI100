//
// Created by Artyom on 3/17/2025.
//

#ifndef CLI_H
#define CLI_H

#include "main.h"

#define CLI_BUFFER_SIZE 1024
#define UART_RECEIVE_TIMEOUT 100
#define UART_TRANSMIT_TIMEOUT 100
#define CMD_MAX_LENGTH 128

#define PROMPT "PCI100$> "
#define CLI_WHITESPACE_DELIMITERS " \t"

// error codes
#define CLI_OK 0
#define CLI_ERROR 1
#define CLI_COMMAND_NOT_FOUND 127

typedef void(*message_handler_t)(const char*);

typedef struct
{
	char name[CMD_MAX_LENGTH];
	message_handler_t handle;
} cmd_handler_t;

typedef struct
{
	uint8_t prompt_trigger;
	UART_HandleTypeDef *huartx;
	message_handler_t handle;
	uint32_t pos;
	uint8_t buf[CLI_BUFFER_SIZE];
} cli_engine_t;


void cli_process(cli_engine_t *engine);
void cli_writeline(UART_HandleTypeDef *huartx, const char *s);
void cli_puts(UART_HandleTypeDef *huartx, const char *s);
void cli_putnl(UART_HandleTypeDef *huartx);
void make_cli_engine(cli_engine_t *engine, UART_HandleTypeDef *huartx, message_handler_t handle);

#endif //CLI_H
