#ifndef ADC_H
# define ADC_H

#define VOLTAGE_MAX 3.3f
#define BIT_RANGE_12 4095.0f

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "typedefs.h"
#include "../cmd/cmd.h"

uint8_t exec_adc(cmd_t * const cmd);

#endif // ADC_H
