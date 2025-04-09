/*
 * cli_led.h
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */

#ifndef SRC_CLI_CLI_LED_CLI_LED_H_
#define SRC_CLI_CLI_LED_CLI_LED_H_

#include <stdint.h>
#include "typedefs.h"


uint8_t cli_led_get(led_t * const led);
uint8_t cli_led(cmd_t * const cmd);


// middlewares
uint8_t cli_led_get_middleware(cmd_t *const cmd, chain_t *const chain);
uint8_t cli_led_reset_middleware(cmd_t *const cmd, chain_t * const chain);
uint8_t cli_led_set_blink_middleware(cmd_t *const cmd, chain_t * const chain);
uint8_t cli_led_toggle_middleware(cmd_t * const cmd, chain_t *const chain);


#endif /* SRC_CLI_CLI_LED_CLI_LED_H_ */
