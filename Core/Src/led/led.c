//
// Created by Artyom on 3/13/2025.
//

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

void led_init(led_t * const led) {
	led->blink_frequency = 0;
	led->blink_mode = BLINK_OFF;
	led->state = LED_OFF;
	set_led_config(led);
}

uint8_t exec_led(cmd_t * const cmd) {

	const char * option = NULL;

	if (cmd->argc > 0) {
		option = cmd->argv[0];
	}

	uint8_t status = 0;

	if (NULL == option || !strcmp(option, "-h") || !strcmp(option, "--help")) {
		printchunk("Usage:", CLI_LED_HELP, NULL);
	}
	else if (!strcmp(option, "off")) {
		status = led_off(cmd);
	}
	else if (!strcmp(option, "blink")) {
		status = led_set_blink(cmd);
	}
	else if (!strcmp(option, "on")) {
		status = led_on(cmd);
	}
	else if (!strcmp(option, "reset")) {
		status = led_reset(cmd);
	}
	else if (!strcmp(option, "get")) {
		status = led_get(cmd);
	} else {
		printf("led: error: invalid option `%s`. See led -h\r\n", option);
		status = APP_INVALID_OPTIONS;
	}

	return status;
}

uint8_t led_get(cmd_t *const cmd) {
	if (cmd->argc != 1) {
		printf("led: %s\r\n", CLI_INVALID_OPTIONS);
		printchunk("Usage:", CLI_LED_GET_HELP, NULL);
		return EINVAL;
	}
	printf("%s\n\r", get_led_state(&cmd->app->led));
	return 0;
}

uint8_t led_reset(cmd_t *const cmd) {

	if (cmd->argc != 1) {
		printf("led: %s\r\n", CLI_INVALID_OPTIONS);
		printchunk("Usage:", CLI_LED_RESET_HELP, NULL);
		return EINVAL;
	}

	set_led_config(&cmd->app->led);
	printf("led mode is now configured by MCU_CFG. ");
	printf("%s\n\r", get_led_state(&cmd->app->led));
	return 0;
}


uint8_t led_set_blink(cmd_t *const cmd) {
	if (cmd->argc != 2) {
		printf("led: %s\r\n", CLI_INVALID_OPTIONS);
		printchunk("Usage:", CLI_LED_BLINK_HELP, NULL);
		return EINVAL;
	}

	app_t * const app = cmd->app;
	const uint32_t frequency = satoi(cmd->argv[1]).val;

	if (frequency > 1 && frequency < 1000) {
		app->led.blink_mode = BLINK_ON;
		app->led.state = LED_ON;
		app->led.blink_frequency = frequency;
		printf("Led frequency set to %s hz\r\n", cmd->argv[1]);
	} else {
		printf("%s\r\n", CLI_LED_INVALID_BLINK_VALUE);
		printchunk("Usage:", CLI_LED_BLINK_HELP, NULL);
	}

	return 0;
}

uint8_t led_off(cmd_t * const cmd) {

	if (cmd->argc != 1) {
		printf("led: %s\r\n", CLI_INVALID_OPTIONS);
		printchunk("Usage:", CLI_LED_ON_OFF_HELP, NULL);
		return EINVAL;
	}

	cmd->app->led.state = LED_OFF;
	cmd->app->led.blink_mode = BLINK_OFF;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);

	printf("%s\n\r", get_led_state(&cmd->app->led));
	return 0;
}


uint8_t led_on(cmd_t * const cmd) {

	if (cmd->argc != 1) {
		printf("led: %s\r\n", CLI_INVALID_OPTIONS);
		printchunk("Usage:", CLI_LED_ON_OFF_HELP, NULL);
		return EINVAL;
	}

	cmd->app->led.state = LED_ON;
	cmd->app->led.blink_mode = BLINK_OFF;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	printf("%s\n\r", get_led_state(&cmd->app->led));
	return 0;
}

void set_led_config(led_t * const led) {
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
    led->blink_frequency = 0;
    led->blink_mode = BLINK_OFF;
    break;
  case 1:
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	led->blink_frequency = 1;
	led->blink_mode = BLINK_ON;
    break;
  case 2 ... 8:
	led->blink_mode = BLINK_ON;
  	led->blink_frequency = fmap[input];
  	break;
  default:
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	led->blink_frequency = 0;
	led->blink_mode = BLINK_OFF;
  }
}


const char *get_led_state(led_t * const led) {

	static char message[128];

	if (led->state == LED_OFF) {
		sprintf(message, CLI_LED_OFF);
	} else if (led->state == LED_ON && led->blink_mode == BLINK_OFF) {
		sprintf(message, CLI_LED_ON);
	} else {
		sprintf(message, "Led is blinking at %lu hz", led->blink_frequency);
	}

	return message;
}

void blink_led(led_t * const led) {

	if (led->blink_mode == BLINK_OFF) {
		return;
	}

	static uint32_t start = 0;

	const uint32_t current_tick = HAL_GetTick();

	if (current_tick >= start + led->blink_frequency) {
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
		start = HAL_GetTick();
	}
}
