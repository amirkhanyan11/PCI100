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

void blink_led(const uint32_t num_cfg_on);
void set_led_config(void);
uint8_t exec_led(cmd_t * const cmd);

#endif // UTILS_H
