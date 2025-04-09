/*
 * spi_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */
#include "main.h"

SPI_HandleTypeDef hspi2 = {
	.Instance = SPI2,
	.Init.Mode = SPI_MODE_MASTER,
	.Init.Direction = SPI_DIRECTION_2LINES,
	.Init.DataSize = SPI_DATASIZE_4BIT,
	.Init.CLKPolarity = SPI_POLARITY_LOW,
	.Init.CLKPhase = SPI_PHASE_1EDGE,
	.Init.NSS = SPI_NSS_SOFT,
	.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2,
	.Init.FirstBit = SPI_FIRSTBIT_MSB,
	.Init.TIMode = SPI_TIMODE_DISABLE,
	.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE,
	.Init.CRCPolynomial = 7,
	.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE,
	.Init.NSSPMode = SPI_NSS_PULSE_ENABLE
};



//SPI_Init(TT_SPI2, POLARITY_LOW,  );

//#define POLARITY_LOW 0
//#define POLARITY_HIGH 1
/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
void MX_SPI_Init(SPI_HandleTypeDef * const hspix, int pol )
{

//	switch(pol) {
//	case POLARITY_LOW:
//		Init.CLKPolarity = SPI_POLARITY_LOW;
//	}

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/

  if (HAL_SPI_Init(hspix) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}
