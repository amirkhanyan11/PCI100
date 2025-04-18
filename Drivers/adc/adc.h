/*
 * adc.h
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#ifndef DRIVERS_ADC_ADC_H_
#define DRIVERS_ADC_ADC_H_

#define VOLTAGE_MAX 3.3f
#define BIT_RANGE_12 4095.0f
#define COUNTER 10
#define ADC_SUPPORTED_MAX_CHANNELS_SIZE 19


#include "main.h"

void 	adc_channels_handler(ADC_HandleTypeDef * const hadcx, uint8_t channel);
uint8_t adc_get_channel(uint8_t typedef_handler, uint8_t id);
uint8_t adc_get_channels_size(void);
uint8_t	adc_read(uint8_t hadcx, uint8_t adc_channel_id, float * const res);

#endif /* DRIVERS_ADC_ADC_H_ */
