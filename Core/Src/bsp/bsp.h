/*
 * bsp.h
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_

#include "main.h"
#include "typedefs.h"

struct bsp_s
{
	UART_HandleTypeDef  *huartx;
	DAC_HandleTypeDef 	*hdacx;
	I2C_HandleTypeDef 	*hi2cx;
	ADC_HandleTypeDef	*hadcx;
	SPI_HandleTypeDef 	*hspix;
};

void bsp_init(bsp_t * const bsp,
		DAC_HandleTypeDef * const hdacx,
		ADC_HandleTypeDef * const hadcx,
		UART_HandleTypeDef * const huartx,
		I2C_HandleTypeDef * const hi2cx,
		SPI_HandleTypeDef * const hspix);


#endif /* SRC_BSP_BSP_H_ */

