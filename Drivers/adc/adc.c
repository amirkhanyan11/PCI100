/*
 * adc.c
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#include "adc.h"
#include <string.h>
#include "bsp.h"

uint8_t adc_read(ADC_HandleTypeDef * const hadcx, uint32_t adc_channel, float * const res)
{
	adc_channels_handler(hadcx, adc_channel);

	HAL_ADC_Start(hadcx);

	*res = 0;

	for (uint8_t i = 0; i < COUNTER; ++i) {
		HAL_ADC_PollForConversion(hadcx, 10);
		*res += HAL_ADC_GetValue(hadcx);
	}
	*res /= COUNTER;
	*res *= VOLTAGE_MAX / BIT_RANGE_12;

	return (HAL_ADC_Stop(hadcx));
}


