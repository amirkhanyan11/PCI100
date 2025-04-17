/*
 * dac_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include <dac.h>
#include "config.h"

DAC_HandleTypeDef hdac;
static DAC_TypeDef * instance_table[] = {DAC};
static const chnl_info_t *dac_table;
static uint8_t	dac_channels_size;

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
void dac_init(const chnl_info_t *table)
{
	dac_table = table;
	hdac.Instance = instance_table[dac_table->typedef_handler - 1];

	/** DAC Initialization
	*/
	if (HAL_DAC_Init(&hdac) != HAL_OK)
	{
		error_handler();
	}

	uint8_t j = 0;
	for (uint8_t i = 0; dac_table[i].typedef_handler != 0; ++i) {
		for (; dac_table[i].chnl_table[j] != 0; ++j) {
			dac_channels_handler(&hdac, dac_table[i].chnl_table[j]);
		}
	}
	dac_channels_size = j;
}

uint8_t dac_get_channels_size(void)
{
	return dac_channels_size;
}

uint32_t dac_get_channel(uint8_t channel_id)
{
	if (channel_id >= dac_channels_size) {
		return -1;
	}

	return dac_table->chnl_table[channel_id - 1];
}

void dac_channels_handler(DAC_HandleTypeDef * const hdacx, uint8_t channel)
{
	DAC_ChannelConfTypeDef sConfig = {0};

	/** DAC channel config
	*/
	sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;

	if (HAL_DAC_ConfigChannel(hdacx, &sConfig, channel) != HAL_OK)
	{
		error_handler();
	}

	HAL_DAC_Start(hdacx, channel);
}
