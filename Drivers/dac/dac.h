//
// Created by Artyom on 3/17/2025.
//

#ifndef DAC_H
#define DAC_H

#include "main.h"
#include "../cmd/cmd.h"
#include "../cli/cli.h"
#include "../utils/utils.h"
#include "../led/led.h"

#define DAC_MAX_VALUE 1
#define DAC_COUNT 1
#define DAC_SUPPORTED_MAX_CHANNELS_SIZE 2

uint8_t 			dac_write(DAC_HandleTypeDef * const hdacx, const uint32_t channel, const uint32_t alignment, const uint16_t value);
void				dac_channels_handler(DAC_HandleTypeDef * const hdacx, uint8_t channel_id);
HAL_StatusTypeDef	dac_channel_init(DAC_HandleTypeDef * const hdacx, uint32_t channel);
uint8_t				dac_get_channels_size(void);
#endif //DAC_H
