/*
 * cli_adc.h
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#ifndef SRC_CLI_CLI_ADC_CLI_ADC_H_
#define SRC_CLI_CLI_ADC_CLI_ADC_H_

#include "typedefs.h"
#include <stdbool.h>

uint8_t cli_adc(cmd_t * const cmd);

// utils
uint8_t __adc_err(const char * help);
bool 	adc_supported_channel(uint8_t channel_id);

// middlewares
uint8_t cli_adc_read_middleware(cmd_t * const cmd, chain_t *const chain);



#endif /* SRC_CLI_CLI_ADC_CLI_ADC_H_ */
