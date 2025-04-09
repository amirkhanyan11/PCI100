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
uint8_t __adc_err(void);
bool 	adc_supported_channel(uint8_t channel_id);
uint8_t cli_adc_read_middleware(cmd_t * const cmd, chain_t *const chain);
uint8_t cli_adc_read_route(cmd_t * const cmd);



#endif /* SRC_CLI_CLI_ADC_CLI_ADC_H_ */
