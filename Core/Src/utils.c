//
// Created by Artyom on 3/18/2025.
//

#include "utils.h"

extern UART_HandleTypeDef huart1;

void uart_echo(void) {
  uint8_t rxbuf = 0;
  if (HAL_OK == HAL_UART_Receive(&huart1, &rxbuf, 1, 10)) {
    HAL_UART_Transmit(&huart1, &rxbuf, 1, 10);
  }
}