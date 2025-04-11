/*
 * adc.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "config.h"
#include "adc.h"

static uint32_t adc_channels[ADC_SUPPORTED_MAX_CHANNELS_SIZE];
static uint8_t adc_channels_size;

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
void adc_init(ADC_HandleTypeDef * const hadcx, ADC_TypeDef * const instance, uint32_t resolution, uint32_t clock_prescaler)
{
	hadcx->Instance = instance;
	hadcx->Init.ClockPrescaler = clock_prescaler;
	hadcx->Init.Resolution = resolution;
	hadcx->Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadcx->Init.ContinuousConvMode = DISABLE;
	hadcx->Init.DiscontinuousConvMode = DISABLE;
	hadcx->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadcx->Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadcx->Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadcx->Init.NbrOfConversion = 1;
	hadcx->Init.DMAContinuousRequests = DISABLE;
	hadcx->Init.EOCSelection = ADC_EOC_SINGLE_CONV;

	if (HAL_ADC_Init(hadcx) != HAL_OK) {
	error_handler();
	}

}

HAL_StatusTypeDef adc_channel_init(ADC_HandleTypeDef * const hadcx, uint32_t channel)
{
	if (adc_channels_size == ADC_SUPPORTED_MAX_CHANNELS_SIZE) {
		return HAL_ERROR;
	}

	adc_channels[adc_channels_size] = channel;


	adc_channels_size += 1;

	adc_channels_handler(hadcx, adc_channels_size);

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
		error_handler();
	}
}
