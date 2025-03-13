//
// Created by Artyom on 3/13/2025.
//
#include "utils.h"
#include <stdint.h>
#include <unistd.h>

extern UART_HandleTypeDef huart1;

void uart_echo(void) {
    uint8_t rxbuf = 0;

    if (HAL_OK == HAL_UART_Receive(&huart1, &rxbuf, 1, 1000))
    {
        HAL_UART_Transmit(&huart1, &rxbuf, 1, 1000);
    }
}

void blink_led(const uint32_t *freq_arr, const uint8_t freq_arr_size, const uint8_t num_cfg_on)
{
    if (num_cfg_on >= freq_arr_size) {
        return;
    }
    switch (num_cfg_on)
    {
    case 0:
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
        break;
    case 1:
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
        break;
    default:
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
        HAL_Delay(freq_arr[num_cfg_on]);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
        HAL_Delay(freq_arr[num_cfg_on]);
    }
}

uint8_t get_cfg_input_bitwise(void) {

    uint8_t input = 0;

    input |= (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)) << 1);
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)) << 2);
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)) << 3);
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)) << 4);
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)) << 5);
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) << 6);
    input |= (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)) << 7);

    return input;
}

static void prompt_nl(void){
	HAL_UART_Transmit(&huart1, (const uint8_t *)"\r\n", 2, 1000);
}

static void display_prompt(const char *msg) {
    HAL_UART_Transmit(&huart1, (const uint8_t *)msg, (const uint16_t)strlen(msg), 1000);
    prompt_nl();
}

static void flushbuf(uint8_t *buf, uint16_t *pos) {
    *pos = 0;
    memset(buf, 0, BUFFER_SIZE);
}

void start_cli(void) {
    
    static uint8_t buf[BUFFER_SIZE] = {0};
    static uint16_t pos = 0;

    if (HAL_OK == HAL_UART_Receive(&huart1, (buf + pos), 1, 1000)) {
    	if (buf[pos] == '\r'){
    		prompt_nl();
    	}
        if (!strcmp((const char*)buf, "help\r")) {
            display_prompt("led <on/off>");
            flushbuf(buf, &pos);
        } else if (!strcmp((const char*)buf, "led on\r")) {
            display_prompt("OK!");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
            flushbuf(buf, &pos);
        } else if (!strcmp((const char*)buf, "led off\r")) {
        	display_prompt("OK!");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
            flushbuf(buf, &pos);
        } else {
            HAL_UART_Transmit(&huart1, (buf + pos), 1, 1000);
            ++pos;
        }

    }
}
