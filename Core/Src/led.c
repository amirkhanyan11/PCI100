//
// Created by Artyom on 3/13/2025.
//

#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "led.h"
#include "main.h"
#include "cli.h"

extern UART_HandleTypeDef huart1;
extern volatile uint32_t BLINK_FREQ;
extern volatile uint32_t LED_MODE;

static uint32_t start = 0;

void blink_led(const uint32_t frequency) {
  if (LED_MODE == LED_OFF) {
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
    LED_OFF,
    LED_ON,
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
    LED_MODE = LED_OFF;
    break;
  case 1:
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
    LED_MODE = LED_OFF;
    break;
  case 2 ... 8:
    LED_MODE = LED_ON;
    BLINK_FREQ = fmap[input];
  default:
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
    LED_MODE = LED_OFF;
  }
}

static int32_t parse_set_expr(const char* s) {
  if (!s) {
    return -1;
  }
  while (*s && !isdigit(*s)) {
    ++s;
  }
  const int32_t res = atoi(s);
  while (isdigit(*s)) {
    ++s;
  }
  return (*s == '\r') ? res : -1;
}


static void led_cli_handler(const char *message) {
  if (!strcmp(message, "help")) {
      cli_putsnl(&huart1, "led <on/off>");
      cli_putsnl(&huart1, "led mode <get/set/reset>");
  }

  else if (!strcmp(message, "led on")) {
    LED_MODE = LED_ON;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
    cli_putsnl(&huart1, "OK!");
  }

  else if (!strcmp(message, "led off")) {
    LED_MODE = LED_OFF;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
    cli_putsnl(&huart1, "OK!");
  }

  else if (!strncmp(message, "led mode set ", strlen("led mode set "))) {
    const int32_t freq = parse_set_expr(message);
    if (-1 != freq) {
      BLINK_FREQ = freq;
    }
    cli_putsnl(&huart1, "OK!");
  }

  else if (!strcmp(message, "led mode reset")) {
    set_led_config();
    cli_putsnl(&huart1, "led mode is now configured by physical pins");
  }

  else {
    cli_putsnl(&huart1, "error: command not found");
  }
}

void led_cli() {
  cli_engine(&huart1, led_cli_handler);
}
