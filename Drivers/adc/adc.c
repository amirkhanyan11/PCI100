/*
 * adc.c
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#include "adc.h"
#include <string.h>
#include "bsp.h"

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;

static ADC_HandleTypeDef * adc[] = {&hadc1, &hadc2};

uint8_t adc_read(uint8_t hadcx, uint32_t adc_channel, float * const res)
{
	adc_channels_handler(adc[hadcx], adc_channel);

	HAL_ADC_Start(adc[hadcx]);

	*res = 0;

	for (uint8_t i = 0; i < COUNTER; ++i) {
		HAL_ADC_PollForConversion(adc[hadcx], 10);
		*res += HAL_ADC_GetValue(adc[hadcx]);
	}
	*res /= COUNTER;
	*res *= VOLTAGE_MAX / BIT_RANGE_12;

	return (HAL_ADC_Stop(adc[hadcx]));
}


