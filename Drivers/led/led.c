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
	led_mcu_cfg(led);
}

uint8_t led_set_blink(led_t * const led, const uint32_t frequency) {

	if (frequency > 1 && frequency < 1000) {
		led->blink_mode = BLINK_ON;
		led->state = LED_ON;
		led->blink_frequency = frequency;
		return 0;
	}

	return -1;
}

uint8_t led_off(led_t *const led) {
	led->state = LED_OFF;
	led->blink_mode = BLINK_OFF;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	return 0;
}

uint8_t led_on(led_t *const led) {
	led->state = LED_ON;
	led->blink_mode = BLINK_OFF;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	return 0;
}

uint8_t led_mcu_cfg(led_t * const led) {
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

  return 0;
}

void led_blink(led_t * const led) {

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
