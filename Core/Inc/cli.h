//
// Created by Artyom on 3/17/2025.
//

#ifndef CLI_H
#define CLI_H

#include "main.h"


#define UART_BUFFER_SIZE 1024
#define UART_RECEIVE_TIMEOUT 100
#define UART_TRANSMIT_TIMEOUT 100

#define PROMPT "PCI100$> "

// error codes
#define CLI_OK 0
#define CLI_ERROR 1
#define CLI_COMMAND_NOT_FOUND 127

typedef void(*message_handler_t)(const char*);

typedef struct
{
	UART_HandleTypeDef *huartx;
	message_handler_t handle;
	uint32_t pos;
	uint8_t buf[UART_BUFFER_SIZE];
} cli_engine_t;


uint8_t starts_with(const char *s1, const char *s2);
void cli_engine(UART_HandleTypeDef *huartx, message_handler_t handle);
void cli_writeline(UART_HandleTypeDef *huartx, const char *s);
void cli_puts(UART_HandleTypeDef *huartx, const char *s);
void cli_putnl(UART_HandleTypeDef *huartx);

#endif //CLI_H
