/*
 * i2c_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "config.h"

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
void MX_I2C_Init(I2C_HandleTypeDef * const hi2cx)
{

	hi2cx.Instance = I2C1;
	hi2cx.Init.Timing = 0x00303D5B;
	hi2cx.Init.OwnAddress1 = 0;
	hi2cx.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2cx.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2cx.Init.OwnAddress2 = 0;
	hi2cx.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2cx.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2cx.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(hi2cx) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure Analogue filter
	*/
	if (HAL_I2CEx_ConfigAnalogFilter(hi2cx, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure Digital filter
	*/
	if (HAL_I2CEx_ConfigDigitalFilter(hi2cx, 0) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

	/* USER CODE END I2C1_Init 2 */

}
