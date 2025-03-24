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

	cli_writeline(cmd->bsp->engine->huartx, "error: command not found");

	return 127;
}

uint8_t led_get(cmd_t *const cmd) {
	if (cmd->argc != 1) {
		cli_writeline(cmd->bsp->engine->huartx, "led: error: invalid options");
		return EINVAL;

	}
	bsp_t * const bsp = cmd->bsp;

	if (bsp->led_state == LED_OFF) {
		cli_writeline(bsp->engine->huartx, "led is off");
	} else if (bsp->led_state == LED_ON && bsp->blink_mode == BLINK_OFF) {
		cli_writeline(bsp->engine->huartx, "led is on");
	} else {
		cli_puts(bsp->engine->huartx, "led is blinking at ");
		cli_puts(bsp->engine->huartx, static_itoa(bsp->blink_frequency));
		cli_writeline(bsp->engine->huartx, "hz");
	}

	return 0;
}

uint8_t led_reset(cmd_t *const cmd) {

	if (cmd->argc != 1) {
		cli_writeline(cmd->bsp->engine->huartx, "led: error: invalid options");
		return EINVAL;
	}

	set_led_config(cmd->bsp);
	cli_writeline(cmd->bsp->engine->huartx, "led mode is now configured by physical switches");

	return 0;
}


uint8_t led_blink(cmd_t *const cmd) {
	if (cmd->argc != 2) {
		cli_writeline(cmd->bsp->engine->huartx, "led: error: invalid options");
		return EINVAL;
	}

	bsp_t * const bsp = cmd->bsp;
	const uint32_t frequency = atoi(cmd->args[1]);

	switch(frequency) {
	case 1:
	case 10:
	case 20:
	case 50:
	case 100:
	case 500:
	case 1000:
		bsp->blink_mode = BLINK_ON;
		bsp->led_state = LED_ON;
		bsp->blink_frequency = frequency;
		cli_puts(bsp->engine->huartx, "Led frequency set to ");
		cli_puts(bsp->engine->huartx, cmd->args[1]);
		cli_writeline(bsp->engine->huartx, "hz");
		break;
	default:
		cli_writeline(bsp->engine->huartx, "error: frequency not supported");
		return EINVAL;
	}

	return 0;
}

uint8_t led_off(cmd_t * const cmd) {

	if (cmd->argc != 1) {
		cli_writeline(cmd->bsp->engine->huartx, "led: error: invalid options");
	}

	cmd->bsp->led_state = LED_OFF;
	cmd->bsp->blink_mode = BLINK_OFF;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);

	cli_writeline(cmd->bsp->engine->huartx, "Led is now off");
	return 0;
}


uint8_t led_on(cmd_t * const cmd) {

	if (cmd->argc != 1) {
		cli_writeline(cmd->bsp->engine->huartx, "led: error: invalid options");
	}

	cmd->bsp->led_state = LED_ON;
	cmd->bsp->blink_mode = BLINK_OFF;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	cli_writeline(cmd->bsp->engine->huartx, "Led is now on");
	return 0;
}

void blink_led(bsp_t * const bsp) {

	if (bsp->blink_mode == BLINK_OFF) {
		return;
	}

	static uint32_t start = 0;

	const uint32_t current_tick = HAL_GetTick();

	if (current_tick >= start + bsp->blink_frequency) {
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
		start = HAL_GetTick();
	}
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

