//
// Created by Artyom on 3/13/2025.
//
#include "utils.h"
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>

extern UART_HandleTypeDef huart1;
extern uint32_t BLINK_FREQ;
extern uint32_t LED_MODE;

void uart_echo(void) {
    uint8_t rxbuf = 0;
    if (HAL_OK == HAL_UART_Receive(&huart1, &rxbuf, 1, 1000)){
        HAL_UART_Transmit(&huart1, &rxbuf, 1, 1000);
    }
}

void blink_led(const uint8_t frequency)
{
    if (LED_MODE == LED_OFF) {
        return;
    }
    static uint32_t start = HAL_GetTick();
    if (HAL_GetTick() >= start + frequency) {
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
        case LED_OFF:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
        case LED_ON:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
        default:
            blink_led(fmap[input]);
    }
}

static void prompt_nl(void){
	HAL_UART_Transmit(&huart1, (const uint8_t *)"\r\n", 2, 1000);
}

static void display_prompt(const char *msg) {
	prompt_nl();
    HAL_UART_Transmit(&huart1, (const uint8_t *)msg, (const uint16_t)strlen(msg), 1000);
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

static int32_t parse_set_expr(const char *s) {
    if (!s) {
        return -1;
    }
    const char *t = s;
    while (*t && isdigit(*t)) {
        ++t;
    }
    return (*s == '\r') ? atoi(t) : -1;
}


void start_cli(void) {
    
    static uint8_t buf[BUFFER_SIZE] = {0};
    static uint16_t pos = 0;

    static const char *set_prompt = "led mode set ";
    static const uint8_t set_promp_length = strlen(set_prompt);

    if (HAL_OK == HAL_UART_Receive(&huart1, (buf + pos), 1, 1000)) {

        if (!strcmp((const char*)buf, "help\r")) {
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

        } else if (!strncmp((const char*)buf, set_prompt, set_promp_length)) {
            const int32_t freq = parse_set_expr(s);
            if (-1 != freq) {
                BLINK_FREQ = freq;
            }
            display_prompt_and_flush("OK!", buf, &pos);

        } else if (buf[pos] == '\r'){
        	display_prompt_and_flush("command not found:(", buf, &pos);

    	} else if (!strcmp((const char*)buf, "reset\r")) {
            set_led_config();
        	display_prompt_and_flush("led reset", buf, &pos);

        } else {
            HAL_UART_Transmit(&huart1, (buf + pos), 1, 1000);
            ++pos;
        }
    }
}
