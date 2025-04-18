//
// Created by Artyom on 3/17/2025.
//

#ifndef DAC_H
#define DAC_H

#include "main.h"

#define DAC_MAX_VALUE 1
#define DAC_COUNT 1
#define DAC_SUPPORTED_MAX_CHANNELS_SIZE 2

uint8_t 			dac_write(uint8_t hdacx, const uint32_t channel, const uint32_t alignment, const uint16_t value);
void				dac_channels_handler(DAC_HandleTypeDef * const hdacx, uint8_t channel);
uint8_t				dac_get_channels_size(void);
uint32_t			dac_get_channel(uint8_t channel_id);

#endif //DAC_H
