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

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

extern app_t app;
static UART_HandleTypeDef * uart[] = {&huart1, &huart2, &huart3};
fifo_t  UART_FIFO1;
uint8_t rx_buf[UART_RX_BUFFER_SIZE];

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(uart[app.bsp->huartx], (uint8_t *)&ch, 1, UART_TRANSMIT_TIMEOUT);
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

void start_uart_receive_dma (uint8_t huartx)
{
	HAL_UART_Receive_DMA(uart[huartx], rx_buf, UART_RX_BUFFER_SIZE);
}

void uart_transmit(uint8_t huartx, const uint8_t *s, uint32_t len)
{
	HAL_UART_Transmit(uart[huartx], s, len, UART_TRANSMIT_TIMEOUT);
}
