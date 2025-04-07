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

uint8_t exec_dac(cmd_t * const cmd);
uint8_t dac_write(cmd_t * const cmd);
uint8_t dac_help(void);

#endif //DAC_H
