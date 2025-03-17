//
// Created by Artyom on 3/13/2025.
//

#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "main.h"


extern UART_HandleTypeDef huart1;
extern volatile uint32_t BLINK_FREQ;
extern volatile uint32_t LED_MODE;

static uint32_t start = 0;

void uart_echo(void) {
    uint8_t rxbuf = 0;
    if (HAL_OK == HAL_UART_Receive(&huart1, &rxbuf, 1, 10)) {
        HAL_UART_Transmit(&huart1, &rxbuf, 1, 10);
    }
}

void blink_led(const uint32_t frequency)
{
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

    input |= (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)) << 1);
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)) << 2);
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)) << 3);
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)) << 4);
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)) << 5);
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) << 6);
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)) << 7);

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

    switch(input) 
    {
        case 0:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
            LED_MODE = LED_OFF;
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
            LED_MODE = LED_OFF;
            break;
        default:
        	LED_MODE = LED_ON;
            BLINK_FREQ = fmap[input];
    }
}

static void prompt_nl(void){
	HAL_UART_Transmit(&huart1, (const uint8_t *)"\r\n", 2, 10);
}

static void display_prompt(const char *msg) {
	prompt_nl();
    HAL_UART_Transmit(&huart1, (const uint8_t *)msg, (const uint16_t)strlen(msg), 10);
    prompt_nl();
}

static void flushbuf(uint8_t *buf, uint16_t *pos) {
    *pos = 0;
    memset(buf, 0, BUFFER_SIZE);
}

static void display_prompt_and_flush(const char *msg, uint8_t *buf, uint16_t *pos) {
    display_prompt(msg);
    flushbuf(buf, pos);
}

static int32_t parse_set_expr(uint8_t *s) {
    if (!s) {
        return -1;
    }
    const uint8_t *t = s;
    while (*t && !isdigit(*t)) {
        ++t;
    }
    const int32_t res = atoi((const char*)t);
    while(isdigit(*t)) {
    	++t;
    }
    return (*t == '\r') ? res: -1;
}


void start_cli(void) {
    
    static uint8_t buf[BUFFER_SIZE] = {0};
    static uint16_t pos = 0;

    if (HAL_OK == HAL_UART_Receive(&huart1, (buf + pos), 1, 10)) {

    	if (buf[pos] != '\r') {
    		HAL_UART_Transmit(&huart1, (buf + pos), 1, 10);
    		++pos;

    	} else if (!strcmp((const char*)buf, "help\r")) {
            display_prompt("led <on/off>");
            display_prompt_and_flush("led mode <get/set/reset>", buf, &pos);

        } else if (!strcmp((const char*)buf, "led on\r")) {
            LED_MODE = LED_ON;
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
            display_prompt_and_flush("OK!", buf, &pos);

        } else if (!strcmp((const char*)buf, "led off\r")) {
            LED_MODE = LED_OFF;
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
        	display_prompt_and_flush("OK!", buf, &pos);

        } else if (!strncmp((const char*)buf, "led mode set ", strlen("led mode set "))) {
            const int32_t freq = parse_set_expr(buf);
            if (-1 != freq) {
                BLINK_FREQ = freq;
            }
            display_prompt_and_flush("OK!", buf, &pos);

        } else if (!strcmp((const char*)buf, "led mode reset\r")) {
            set_led_config();
        	display_prompt_and_flush("led reset", buf, &pos);

        } else {
        	display_prompt_and_flush("command not found:(", buf, &pos);
        }
    }
}
