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



uint8_t exec_led(cmd_t * const cmd) {
	return 0;
}



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

