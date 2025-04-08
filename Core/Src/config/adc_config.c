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

uint32_t adc_channels[ADC_SUPPORTED_CHANNELS_SIZE] = {ADC_CHANNEL_10};

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
void MX_ADC_Init(ADC_HandleTypeDef * const hadcx)
{
  if (HAL_ADC_Init(hadcx) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  adc_channels_handler(hadcx, 1);

}

void adc_channels_handler(ADC_HandleTypeDef *hadcx, uint8_t channel_id)
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
