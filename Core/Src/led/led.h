//
// Created by Artyom on 3/13/2025.
//

#ifndef SRC_CMD_LED_H
#define SRC_CMD_LED_H

#include <stdint.h>
//#include "cmd.h"
#include "typedefs.h"

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

struct led_s
{
	uint32_t 			blink_frequency;
	uint8_t 			blink_mode;
	uint8_t 			state;
};

void		led_init(led_t * const led);

void 		set_led_config(led_t * const led);
uint8_t 	led_on(cmd_t * const cmd);
uint8_t 	led_off(cmd_t * const cmd);
uint8_t 	led_set_blink(cmd_t * const cmd);
uint8_t 	exec_led(cmd_t * const cmd);
uint8_t 	led_reset(cmd_t *const cmd);
uint8_t 	led_get(cmd_t *const cmd);
const char  *get_led_state(led_t * const led);
void blink_led(led_t * const led);

#endif // SRC_CMD_LED_H
