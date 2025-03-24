//
// Created by Artyom on 3/17/2025.
//

#include "dac.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

extern UART_HandleTypeDef huart1;
extern DAC_HandleTypeDef hdac;

uint8_t exec_dac(cmd_t * const cmd) {
	return 0;
}

static void dac_write(uint32_t dac_id, uint16_t dac_value) {

	static DAC_HandleTypeDef dac_map[DAC_COUNT] = {0};

	dac_map[0] = hdac;

	// mapping dac objects to id's with offset of 1. Dac with id 1 will be in the 0'th position.
	HAL_DAC_SetValue((dac_map + dac_id - 1), DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_value);
}
