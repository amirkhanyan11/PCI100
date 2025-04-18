/*
 * uart.h
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#ifndef UART_UART_H_
#define UART_UART_H_

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

#define UART_RECEIVE_TIMEOUT 100
#define UART_TRANSMIT_TIMEOUT 100

void start_uart_receive_dma (uint8_t huartx);
void uart_transmit(uint8_t huartx, const uint8_t *s, uint32_t len);

#endif /* UART_UART_H_ */
