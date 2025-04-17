//
// Created by Artyom on 3/17/2025.
//

#include <dac.h>
#include "main.h"
#include "cli.h"

extern DAC_HandleTypeDef hdac;
static DAC_HandleTypeDef *dac[] = {&hdac};


uint8_t dac_write(uint8_t hdacx, const uint32_t channel, const uint32_t alignment, const uint16_t value) {
	HAL_DAC_SetValue(dac[hdacx], channel, alignment, value);
	return 0;
}

