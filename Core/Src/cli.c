//
// Created by Artyom on 3/17/2025.
//
#include "cli.h"
#include <string.h>

void cli_engine(UART_HandleTypeDef *huartx, message_handler_t handle) {

  static uint8_t buf[UART_BUFFER_SIZE] = {0};
  static uint16_t pos = 0;

  HAL_UART_Transmit(huartx, PROMPT, strlen(PROMPT), UART_TRANSMIT_TIMEOUT);

  if (HAL_OK == HAL_UART_Receive(huartx, buf + pos, 1, UART_RECEIVE_TIMEOUT)) {
    if (buf[pos] == '\r') {
      buf[pos] = '\0';
      cli_putnl(huartx);
      handle((const char *)buf);
      memset(buf, 0, UART_BUFFER_SIZE);
      pos = 0;
    } else {
      HAL_UART_Transmit(huartx, buf + pos, 1, UART_TRANSMIT_TIMEOUT);
      ++pos;
    }
  }
}

uint8_t command_not_found_handler(const char *message) {
	cli_writeline(&huart1, "error: command not found");
	return CLI_COMMAND_NOT_FOUND;
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

uint8_t starts_with(const char *s1, const char *s2) {
  return (strncmp(s1, s2, strlen(s2)) == 0);
}
