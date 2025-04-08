/*
 * bsp.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "bsp.h"
#include "typedefs.h"
#include "main.h"

void bsp_config(bsp_t * const bsp,
		DAC_HandleTypeDef *  const hdacx,
		ADC_HandleTypeDef *  const hadcx,
		UART_HandleTypeDef * const huartx,
		I2C_HandleTypeDef * const hi2cx,
		SPI_HandleTypeDef * const hspix
) {

	bsp->hdacx = hdacx;
	bsp->hadcx = hadcx;
	bsp->huartx = huartx;
	bsp->hi2cx = hi2cx;
	bsp->hspix = hspix;

	HAL_DAC_Start(bsp->hdacx, DAC_CHANNEL_2);
}


