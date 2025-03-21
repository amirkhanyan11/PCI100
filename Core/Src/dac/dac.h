//
// Created by Artyom on 3/17/2025.
//

#ifndef DAC_H
#define DAC_H

#include "main.h"
#include "../cli/cli.h"
#include "../utils/utils.h"
#include "../led/led.h"

#define INVALID_DAC_VALUE 70
#define DAC12_MAX 4096
#define DAC_COUNT 1

uint8_t dac_message_handler(const char *message);

#endif //DAC_H
