/*
 * i2c_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "config.h"

I2C_HandleTypeDef hi2c1 = {
	.Instance = I2C1,
	.Init.Timing = 0x00303D5B,
	.Init.OwnAddress1 = 0,
	.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT,
	.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE,
	.Init.OwnAddress2 = 0,
	.Init.OwnAddress2Masks = I2C_OA2_NOMASK,
	.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE,
	.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE
};

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
void MX_I2C_Init(I2C_HandleTypeDef * const hi2cx)
{

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
