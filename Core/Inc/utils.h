//
// Created by Artyom on 3/13/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdint.h>
#include "main.h"

#define LED_ON 0
#define LED_OFF 1
#define BLINK_1 1000
#define BLINK_2 500
#define BLINK_10 100
#define BLINK_20 50
#define BLINK_50 20
#define BLINK_100 10
#define BLINK_1000 1
#define CFG_PIN_MAX 8

#define BUFFER_SIZE 1024

void uart_echo(void);
void blink_led(const uint8_t num_cfg_on);
void set_led_config(void);
void start_cli(void);

#endif // UTILS_H
