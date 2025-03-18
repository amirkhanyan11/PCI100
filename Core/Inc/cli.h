//
// Created by Artyom on 3/17/2025.
//

#ifndef CLI_H
#define CLI_H

#include "main.h"

#define UART_BUFFER_SIZE 1024
#define UART_RECEIVE_TIMEOUT 100
#define UART_TRANSMIT_TIMEOUT 100

typedef void(*message_handler_t)(const char*);

void cli_engine(UART_HandleTypeDef *huartx, message_handler_t handle);
void cli_putsnl(UART_HandleTypeDef *huartx, const char *s);
void cli_puts(UART_HandleTypeDef *huartx, const char *s);
void cli_putnl(UART_HandleTypeDef *huartx);

#endif //CLI_H
