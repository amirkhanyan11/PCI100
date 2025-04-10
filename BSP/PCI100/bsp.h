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

struct pci100_bsp_s
{
	UART_HandleTypeDef * const huartx;
	DAC_HandleTypeDef * const hdacx;
	I2C_HandleTypeDef * const hi2cx;
	ADC_HandleTypeDef * const hadcx;
	SPI_HandleTypeDef * const hspix;
};

void			bsp_init(void);
pci100_bsp_t	*bsp_get(void);


#endif /* SRC_BSP_BSP_H_ */

