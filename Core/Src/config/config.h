/*
 * config.h
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#ifndef SRC_CONFIG_CONFIG_H_
#define SRC_CONFIG_CONFIG_H_

#include "main.h"


void MX_SPI_Init(SPI_HandleTypeDef * const hspix);

//void MX_DMA_Init(?);

void MX_I2C_Init(I2C_HandleTypeDef * const hi2cx);

//void MX_USART_UART_Init(UART_HandleTypeDef * const huartx);

void MX_ADC_Init(ADC_HandleTypeDef * const hadcx);


//void MX_DAC_Init(DAC_HandleTypeDef * const hdacx);



#endif /* SRC_CONFIG_CONFIG_H_ */
