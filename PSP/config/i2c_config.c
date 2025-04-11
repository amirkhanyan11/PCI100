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
void i2c_init(I2C_HandleTypeDef * const hi2cx, I2C_TypeDef * const instance, uint32_t timing, uint32_t address_mode)
{

	hi2cx->Instance = instance;
	hi2cx->Init.Timing = timing;
	hi2cx->Init.OwnAddress1 = 0;
	hi2cx->Init.AddressingMode = address_mode;
	hi2cx->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2cx->Init.OwnAddress2 = 0;
	hi2cx->Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2cx->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2cx->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(hi2cx) != HAL_OK)
	{
		error_handler();
	}

	/** Configure Analogue filter
	*/
	if (HAL_I2CEx_ConfigAnalogFilter(hi2cx, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		error_handler();
	}

	/** Configure Digital filter
	*/
	if (HAL_I2CEx_ConfigDigitalFilter(hi2cx, 0) != HAL_OK)
	{
		error_handler();
	}

	gpio_pin_set(PCI_RESET, ON);


}
