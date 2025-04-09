/*
 * led_set_blink_middleware.c
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

uint8_t cli_led_set_blink_middleware(cmd_t *const cmd, chain_t * const chain) {
	if (cmd->argc != 2) {
		printf("led: %s\r\n", CLI_INVALID_OPTIONS);
		printchunk("Usage:", CLI_LED_BLINK_HELP, NULL);
		return EINVAL;
	}

	const uint32_t frequency = satoi(cmd->argv[1]).val;

	const chain_fn_t next = chain_get_next(chain);

	if (!next) {
		printf("led: error: something went wrong\r\n");
	}

	const uint8_t status = next(&cmd->app->led, frequency);

	if (status) {
		printf("%s\r\n", CLI_LED_INVALID_BLINK_VALUE);
		printchunk("Usage:", CLI_LED_BLINK_HELP, NULL);
		return -1;
	}

	printf("Led frequency set to %s hz\r\n", cmd->argv[1]);
	return 0;
}
