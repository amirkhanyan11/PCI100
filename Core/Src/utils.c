//
// Created by Artyom on 3/18/2025.
//

#include "utils.h"

#define UINT32_MAX_DIGITS 10

extern UART_HandleTypeDef huart1;

void uart_echo(void) {
  uint8_t rxbuf = 0;
  if (HAL_OK == HAL_UART_Receive(&huart1, &rxbuf, 1, 10)) {
    HAL_UART_Transmit(&huart1, &rxbuf, 1, 10);
  }
}

const char *static_itoa(uint32_t n) {
  static char res[UINT32_MAX_DIGITS + 1] = {0};
  uint8_t i = 0;

  while (n > 9) {
    res[i] = '0' + (n % 10);
    n /= 10;
    ++i;
  }
  res[i] = '0' + n;
  res[i + 1] = '\0';

  for (int8_t j = 0; j < i; ++j, --i) {
    const char t = res[j];
    res[j] = res[i];
    res[i] = t;
  }

  return res;
}