/*
 * adc.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "config.h"
#include "adc.h"

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

static uint8_t adc_channels_size;

static ADC_TypeDef * instance_table[] = {ADC1, ADC2};

static const chnl_info_t *adc_table;


/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
void adc_init(const chnl_info_t *table, uint32_t resolution, uint32_t clock_prescaler)
{
	adc_table = table;

	hadc1.Instance = instance_table[adc_table->typedef_handler - 1];
	hadc1.Init.ClockPrescaler = clock_prescaler;
	hadc1.Init.Resolution = resolution;
	hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

	if (HAL_ADC_Init(&hadc1) != HAL_OK) {
	error_handler();
	}
	uint8_t j = 0;
	for (uint8_t i = 0; adc_table[i].typedef_handler != 0; ++i) {
		for (; adc_table[i].chnl_table[j] != 0; ++j) {
			adc_channels_handler(&hadc1, adc_table[i].chnl_table[j]);
		}
	}
	adc_channels_size = j;
}

uint8_t adc_get_channels_size(void)
{
	return adc_channels_size;
}

void adc_channels_handler(ADC_HandleTypeDef * const hadcx, uint8_t channel)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = channel;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(hadcx, &sConfig) != HAL_OK)
	{
		error_handler();
	}
}
