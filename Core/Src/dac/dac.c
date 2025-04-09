//
// Created by Artyom on 3/17/2025.
//

#include "main.h"
#include "dac.h"
#include "cli.h"

uint8_t dac_write(DAC_HandleTypeDef * const hdacx, const uint32_t channel, const uint32_t alignment, const uint16_t value) {
	HAL_DAC_SetValue(hdacx, channel, alignment, value);
	return 0;
}



