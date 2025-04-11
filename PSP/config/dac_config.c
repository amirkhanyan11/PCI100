/*
 * dac_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "config.h"
#include "dac.h"

static uint32_t	dac_channels[DAC_SUPPORTED_MAX_CHANNELS_SIZE];
static uint8_t	dac_channels_size;

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
void dac_init(DAC_HandleTypeDef * const hdacx, DAC_TypeDef * const instance)
{

	hdacx->Instance = instance;

	/** DAC Initialization
	*/
	if (HAL_DAC_Init(hdacx) != HAL_OK)
	{
	Error_Handler();
	}
}

HAL_StatusTypeDef dac_channel_init(DAC_HandleTypeDef * const hdacx, uint32_t channel)
{
	if (dac_channels_size == DAC_SUPPORTED_MAX_CHANNELS_SIZE) {
		return HAL_ERROR;
	}

	dac_channels[dac_channels_size] = channel;


	dac_channels_size += 1;

	dac_channels_handler(hdacx, dac_channels_size);

	return HAL_OK;
}

uint8_t dac_get_channels_size(void)
{
	return dac_channels_size;
}

void dac_channels_handler(DAC_HandleTypeDef * const hdacx, uint8_t channel_id)
{
	DAC_ChannelConfTypeDef sConfig = {0};

	/** DAC channel config
	*/
	sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;

	if (HAL_DAC_ConfigChannel(hdacx, &sConfig, dac_channels[channel_id - 1]) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_DAC_Start(hdacx, dac_channels[channel_id - 1]);
}
