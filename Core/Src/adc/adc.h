#ifndef ADC_H
# define ADC_H

#define VOLTAGE_MAX 3.3f
#define BIT_RANGE_12 4095.0f
#define COUNTER 10
#define ADC_SUPPORTED_CHANNELS_SIZE 1


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "typedefs.h"
#include "cmd.h"

uint8_t exec_adc(cmd_t * const cmd);
void adc_channels_handler(ADC_HandleTypeDef *hadcx, uint8_t channel_id);

#endif // ADC_H
