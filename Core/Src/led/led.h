//
// Created by Artyom on 3/13/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "../cmd/cmd.h"

#define LED_ON 0
#define LED_OFF 1
#define BLINK_ON 0
#define BLINK_OFF 1
#define BLINK_1 1000
#define BLINK_2 500
#define BLINK_10 100
#define BLINK_20 50
#define BLINK_50 20
#define BLINK_100 10
#define BLINK_1000 1
#define CFG_PIN_MAX 8

#define BUFFER_SIZE 1024

uint8_t led_on(cmd_t * const cmd);
uint8_t led_off(cmd_t * const cmd);
uint8_t led_blink(cmd_t * const cmd);
const char *get_led_mode(bsp_t * const bsp);
void set_led_config(bsp_t * const bsp);
uint8_t exec_led(cmd_t * const cmd);
uint8_t led_reset(cmd_t *const cmd);
uint8_t led_get(cmd_t *const cmd);
const char *get_led_state(bsp_t * const bsp);
uint8_t led_help(void);

#endif // UTILS_H
