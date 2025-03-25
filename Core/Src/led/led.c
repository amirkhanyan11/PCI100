//
// Created by Artyom on 3/13/2025.
//

#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "../cli/cli.h"
#include "../utils/utils.h"
#include <errno.h>
#include "led.h"
#include "../cli/cli_string_literals.h"

uint8_t exec_led(cmd_t * const cmd) {

	const char * const option = cmd->args[0];

	if (!strcmp(option, "on")) {
		return led_on(cmd);
	}
	else if (!strcmp(option, "off")) {
		return led_off(cmd);
	}
	else if (!strcmp(option, "blink")) {
		return led_blink(cmd);
	}
	else if (!strcmp(option, "reset")) {
		return led_reset(cmd);
	}
	else if (!strcmp(option, "get")) {
		return led_get(cmd);
	}

	printf(CLI_COMMAND_NOT_FOUND);

	return 127;
}

uint8_t led_get(cmd_t *const cmd) {
	if (cmd->argc != 1) {
		printf("led: %s", CLI_INVALID_OPTIONS);
		return EINVAL;
	}
	printf("%s\n\r", get_led_state(cmd->bsp));
	return 0;
}

uint8_t led_reset(cmd_t *const cmd) {

	if (cmd->argc != 1) {
		printf("led: %s", CLI_INVALID_OPTIONS);
		return EINVAL;
	}

	set_led_config(cmd->bsp);
	printf("led mode is now configured by physical switches. ");
	printf("%s\n\r", get_led_state(cmd->bsp));
	return 0;
}


uint8_t led_blink(cmd_t *const cmd) {
	if (cmd->argc != 2) {
		printf("led: %s", CLI_INVALID_OPTIONS);
		return EINVAL;
	}

	bsp_t * const bsp = cmd->bsp;
	const uint32_t frequency = atoi(cmd->args[1]);

	if (frequency > 1 && frequency < 1000) {
		bsp->blink_mode = BLINK_ON;
		bsp->led_state = LED_ON;
		bsp->blink_frequency = frequency;
		printf("Led frequency set to %s hz\r\n", cmd->args[1]);
	} else {
		printf("led: error: invalid frequency. Valid frequency range: [1 ... 1000]\r\n");
	}

	return 0;
}

uint8_t led_off(cmd_t * const cmd) {

	if (cmd->argc != 1) {
		printf("led: %s", CLI_INVALID_OPTIONS);
		return EINVAL;
	}

	cmd->bsp->led_state = LED_OFF;
	cmd->bsp->blink_mode = BLINK_OFF;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);

	printf("%s\n\r", get_led_state(cmd->bsp));
	return 0;
}


uint8_t led_on(cmd_t * const cmd) {

	if (cmd->argc != 1) {
		printf("led: %s", CLI_INVALID_OPTIONS);
		return EINVAL;
	}

	cmd->bsp->led_state = LED_ON;
	cmd->bsp->blink_mode = BLINK_OFF;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	printf("%s\n\r", get_led_state(cmd->bsp));
	return 0;
}

void set_led_config(bsp_t * const bsp) {
  uint8_t input = 0;

  input |= !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
  input |= !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) << 1;
  input |= !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) << 2;
  input |= !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) << 3;
  input |= !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) << 4;
  input |= !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) << 5;
  input |= !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) << 6;
  input |= !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) << 7;

  static const uint16_t fmap[] = {
    BLINK_OFF,
    BLINK_ON,
    BLINK_1,
    BLINK_2,
    BLINK_10,
    BLINK_20,
    BLINK_50,
    BLINK_100,
    BLINK_1000,
  };

  switch (input) {
  case 0:
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
    bsp->blink_frequency = 0;
    bsp->blink_mode = BLINK_OFF;
    break;
  case 1:
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
    bsp->blink_frequency = 1;
    bsp->blink_mode = BLINK_ON;
    break;
  case 2 ... 8:
	bsp->blink_mode = BLINK_ON;
  	bsp->blink_frequency = fmap[input];
  }
}


const char *get_led_state(bsp_t * const bsp) {

	static char message[128];

	if (bsp->led_state == LED_OFF) {
		sprintf(message, "Led is off");
	} else if (bsp->led_state == LED_ON && bsp->blink_mode == BLINK_OFF) {
		sprintf(message, "Led is on");
	} else {
		sprintf(message, "Led is blinking at %lu hz", bsp->blink_frequency);
	}

	return message;
}
