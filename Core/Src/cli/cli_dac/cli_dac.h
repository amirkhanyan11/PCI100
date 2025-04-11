/*
 * cli_dac.h
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */

#ifndef SRC_CLI_CLI_DAC_CLI_DAC_H_
#define SRC_CLI_CLI_DAC_CLI_DAC_H_

#include "cli.h"
#include <stdbool.h>

// controllers
uint8_t cli_dac_write_middleware(cmd_t * const cmd, chain_t *const chain);


// routers
uint8_t cli_dac(cmd_t * const cmd);
uint8_t cli_dac_write_route(cmd_t * const cmd);

// utils
bool dac_supported_channel(uint8_t channel_id);

#endif /* SRC_CLI_CLI_DAC_CLI_DAC_H_ */
