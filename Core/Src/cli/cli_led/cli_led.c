/*
 * cli_led.c
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

uint8_t cli_led(cmd_t * const cmd) {

	const char * option = NULL;

	if (cmd->argc > 0) {
		option = cmd->argv[0];
	}

	uint8_t status = 0;

	if (NULL == option || !strcmp(option, "-h") || !strcmp(option, "--help")) {
		printchunk("Usage:", CLI_LED_HELP, NULL);
	}
	else if (!strcmp(option, "off")) {
		status = start_chain(cmd, cli_led_toggle_middleware, led_off, NULL);
	}
	else if (!strcmp(option, "blink")) {
		status = start_chain(cmd, cli_led_set_blink_middleware, led_set_blink, NULL);
	}
	else if (!strcmp(option, "on")) {
		status = start_chain(cmd, cli_led_toggle_middleware, led_on, NULL);
	}
	else if (!strcmp(option, "reset")) {
		status = start_chain(cmd, cli_led_reset_middleware, led_mcu_cfg, NULL);
	}
	else if (!strcmp(option, "get")) {
		status = start_chain(cmd, cli_led_get_middleware, cli_led_get, NULL);
	}
	else {
		printf("led: error: invalid option `%s`. See led -h\r\n", option);
		status = APP_INVALID_OPTIONS;
	}

	return status;
}

uint8_t cli_led_get(led_t * const led) {

	if (led->state == LED_OFF) {
		printf("%s\r\n", CLI_LED_OFF);
	} else if (led->state == LED_ON && led->blink_mode == BLINK_OFF) {
		printf("%s\r\n", CLI_LED_ON);
	} else {
		printf("Led is blinking at %lu hz\r\n", led->blink_frequency);
	}
	return 0;
}
