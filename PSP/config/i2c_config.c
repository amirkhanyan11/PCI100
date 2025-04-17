/*
 * i2c_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "config.h"

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
I2C_HandleTypeDef hi2c3;

static I2C_TypeDef * instance_table[] = {I2C1, I2C2, I2C3};


/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
void i2c_init(uint8_t instance, uint32_t timing, uint32_t address_mode)
{
	hi2c1.Instance = instance_table[instance];
	hi2c1.Init.Timing = timing;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = address_mode;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		error_handler();
	}

	/** Configure Analogue filter
	*/
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		error_handler();
	}

	/** Configure Digital filter
	*/
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
	{
		error_handler();
	}

	gpio_pin_set(PCI_RESET, ON);


}
