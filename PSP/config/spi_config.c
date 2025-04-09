/*
 * spi_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */
#include "main.h"
/**
  * @brief SPI Initialization Function
  * @param None
  * @retval None
  */
void MX_SPI_Init(SPI_HandleTypeDef * const hspix, SPI_TypeDef * const instance, uint32_t data_size, uint32_t clk_polarity, uint32_t clk_phase)
{

	hspix->Instance = instance;
	hspix->Init.Mode = SPI_MODE_MASTER;
	hspix->Init.Direction = SPI_DIRECTION_2LINES;
	hspix->Init.DataSize = data_size;
	hspix->Init.CLKPolarity = clk_polarity;
	hspix->Init.CLKPhase = clk_phase;
	hspix->Init.NSS = SPI_NSS_SOFT;
	hspix->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspix->Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspix->Init.TIMode = SPI_TIMODE_DISABLE;
	hspix->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspix->Init.CRCPolynomial = 7;
	hspix->Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspix->Init.NSSPMode = SPI_NSS_PULSE_ENABLE;

  /* SPI parameter configuration*/

  if (HAL_SPI_Init(hspix) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET);

}
