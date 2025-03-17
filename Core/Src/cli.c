//
// Created by Artyom on 3/17/2025.
//
#include "cli.h"
#include <string.h>

void cli_engine(UART_HandleTypeDef *huartx, message_handler_t handle) {

  static uint8_t buf[UART_BUFFER_SIZE] = {0};
  static uint16_t pos = 0;

  if (HAL_OK == HAL_UART_Receive(huartx, buf, 1, UART_RECEIVE_TIMEOUT)) {
    if (buf[pos] == '\r') {
      handle((const char *)buf);
      memset(buf, 0, UART_BUFFER_SIZE);
      pos = 0;
    } else {
      HAL_UART_Transmit(huartx, buf + pos, 1, UART_TRANSMIT_TIMEOUT);
      ++pos;
    }
  }
}

void cli_putsnl(UART_HandleTypeDef *huartx, const char *s) {
  cli_puts(huartx, s);
  cli_putnl(huartx);
}

void cli_puts(UART_HandleTypeDef *huartx, const char *s) {
  HAL_UART_Transmit(huartx, (const uint8_t *)s, strlen(s), UART_TRANSMIT_TIMEOUT);
}

void cli_putnl(UART_HandleTypeDef *huartx) {
  HAL_UART_Transmit(huartx, "\r\n", 2, UART_TRANSMIT_TIMEOUT);
}
