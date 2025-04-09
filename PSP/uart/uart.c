/*
 * uart.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "app.h"
#include "bsp.h"
#include "fifo.h"
#include <stdio.h>
#include "uart.h"

extern app_t app;

fifo_t  UART_FIFO1;
uint8_t rx_buf[UART_RX_BUFFER_SIZE];

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(app.bsp->huartx, (uint8_t *)&ch, 1, UART_TRANSMIT_TIMEOUT);
  return ch;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1) {
		fifo_set(app.engine.buffer, rx_buf[0]);
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_RxCpltCallback(huart);
}
