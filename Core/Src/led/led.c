//
// Created by Artyom on 3/13/2025.
//

#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "led.h"
#include "main.h"
#include "../cli/cli.h"
#include "../utils/utils.h"

extern UART_HandleTypeDef huart1;
uint32_t BLINK_FREQ;
uint8_t BLINK_MODE = BLINK_OFF;
uint8_t LED_STATE = LED_OFF;

static uint32_t start = 0;

static const char *get_led_mode(void) {
  if (LED_STATE == LED_OFF) {
	  return "off";
  } else if (LED_STATE == LED_ON && BLINK_MODE == BLINK_OFF) {
	  return "on";
  } else {
	  return static_itoa(BLINK_FREQ);
  }
}

void blink_led(const uint32_t frequency) {
  if (BLINK_MODE == BLINK_OFF) {
    return;
  }
  const uint32_t current_tick = HAL_GetTick();
  if (current_tick >= start + frequency) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
    start = HAL_GetTick();
  }
}

void set_led_config(void) {
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
    BLINK_FREQ = 0;
    BLINK_MODE = BLINK_OFF;
    break;
  case 1:
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
    BLINK_FREQ = 1;
    BLINK_MODE = BLINK_ON;
    break;
  case 2 ... 8:
    BLINK_MODE = BLINK_ON;
    BLINK_FREQ = fmap[input];
  }
}

static int32_t parse_set_expr(const char* s) {
  if (!s) {
    return -1;
  }
  while (*s && !isdigit((const uint8_t)*s)) {
    ++s;
  }
  const int32_t res = atoi(s);
  while (isdigit((const uint8_t)*s)) {
    ++s;
  }
  return (*s == '\0') ? res : -1;
}


static uint8_t led_blink_handler(const int32_t val) {
	if (val < 0) {
		cli_writeline(&huart1, "error: bad frequency value: Available values are 1, 10, 20, 50, 100, 500, 1000");
		return CLI_ERROR;
	}
	switch(val) {
	case 1:
	case 10:
	case 20:
	case 50:
	case 100:
	case 500:
	case 1000:
		BLINK_MODE = BLINK_ON;
		LED_STATE = LED_ON;
		BLINK_FREQ = val;
		cli_puts(&huart1, "Led frequency set to ");
		cli_writeline(&huart1, get_led_mode());
		break;
	default:
		cli_writeline(&huart1, "error: frequency not supported");
		return CLI_ERROR;
	}

	return CLI_OK;
}

void led_message_handler(const char *message) {

  if (!strcmp(message, "led on")) {
    BLINK_MODE = BLINK_OFF;
    LED_STATE = LED_ON;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
    cli_writeline(&huart1, "Led is now on");
  }

  else if (!strcmp(message, "led off")) {
    BLINK_MODE = BLINK_OFF;
    LED_STATE = LED_OFF;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
    cli_writeline(&huart1, "Led is now off");
  }

  else if (starts_with(message, "led blink ")) {
    led_blink_handler(parse_set_expr(message));
  }

  else if (!strcmp(message, "led reset")) {
    set_led_config();
    cli_writeline(&huart1, "led mode is now configured by physical switches");
  }

  else if (!strcmp(message, "led get state")) {
    cli_puts(&huart1, "led mode is ");
    cli_writeline(&huart1, get_led_mode());
  }

}

