/*
 * cli_led_reset_middleware.c
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */


#include "cli_led.h"
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "cli.h"
#include "utils.h"
#include <errno.h>
#include "led.h"
#include "cmd.h"
#include "cli_string_literals.h"

uint8_t cli_led_reset_middleware(cmd_t *const cmd, chain_t * const chain) {

	if (cmd->argc != 1) {
		printf("led: %s\r\n", CLI_INVALID_OPTIONS);
		printchunk("Usage:", CLI_LED_RESET_HELP, NULL);
		return EINVAL;
	}

	const chain_fn_t next = chain_get_next(chain);

	if (!next) {
		printf("led: error: something went wrong\r\n");
	}

	next(&cmd->app->led);

	printf("led mode is now configured by MCU_CFG. ");
	cli_led_get(&cmd->app->led);
	return 0;
}
