/*
 * spi_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */
#include "main.h"
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;

static SPI_TypeDef *  instance_table[] = {SPI1, SPI2, SPI3};

/**
  * @brief SPI Initialization Function
  * @param None
  * @retval None
  */
void spi_init(uint8_t instance, uint32_t data_size, uint32_t clk_polarity, uint32_t clk_phase,
		uint32_t baud_rate_prescaler)
{

	hspi2.Instance = instance_table[instance];
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = data_size;
	hspi2.Init.CLKPolarity = clk_polarity;
	hspi2.Init.CLKPhase = clk_phase;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = baud_rate_prescaler;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 7;
	hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;

	/* SPI parameter configuration*/

	if (HAL_SPI_Init(&hspi2) != HAL_OK)
	{
		error_handler();
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET);

}
