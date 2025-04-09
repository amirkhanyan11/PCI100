/*
 * adc.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "config.h"
#include "adc.h"

ADC_HandleTypeDef hadc1 = {
	.Instance = ADC1,
	.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2,
	.Init.Resolution = ADC_RESOLUTION_12B,
	.Init.ScanConvMode = ADC_SCAN_DISABLE,
	.Init.ContinuousConvMode = DISABLE,
	.Init.DiscontinuousConvMode = DISABLE,
	.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE,
	.Init.ExternalTrigConv = ADC_SOFTWARE_START,
	.Init.DataAlign = ADC_DATAALIGN_RIGHT,
	.Init.NbrOfConversion = 1,
	.Init.DMAContinuousRequests = DISABLE,
	.Init.EOCSelection = ADC_EOC_SINGLE_CONV
};

uint32_t adc_channels[ADC_SUPPORTED_MAX_CHANNELS_SIZE] = {0};
static uint8_t adc_channels_size;

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
void MX_ADC_Init(ADC_HandleTypeDef * const hadcx, const uint32_t * const channels)
{
  if (HAL_ADC_Init(hadcx) != HAL_OK) {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  if (adc_channels_init(hadcx, channels) != HAL_OK) {
	Error_Handler();
  }

}

HAL_StatusTypeDef adc_channels_init(ADC_HandleTypeDef * const hadcx, const uint32_t * const channels)
{
	if (channels == NULL || *channels == 0) {
		return HAL_ERROR;
	}
	for (; channels[adc_channels_size] != 0; ++adc_channels_size){
		if (adc_channels_size == ADC_SUPPORTED_MAX_CHANNELS_SIZE) {
			return HAL_ERROR;
		}
		adc_channels[adc_channels_size] = channels[adc_channels_size];
	}
	adc_channels_size += 1;
	adc_channels_handler(hadcx, 1);
	return HAL_OK;
}

uint8_t adc_get_channels_size(void)
{
	return adc_channels_size;
}

void adc_channels_handler(ADC_HandleTypeDef * const hadcx, uint8_t channel_id)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = adc_channels[channel_id - 1];
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(hadcx, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
}
