//
// Created by Artyom on 3/13/2025.
//
#include "utils.h"

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

static void display_help_prompt(void) {
    static const uint8_t prompt[] = "gri axpers\r\n";
    HAL_UART_Transmit(&huart1, prompt, strlen(prompt), 1000);
}


void start_cli(void) {
    
    static uint8_t buf[BUFFER_SIZE] = {0};
    static uint16_t bufferptr = 0;

    if (HAL_OK == HAL_UART_Receive(&huart1, (buf + bufferptr), 1, 1000)) {
        if (!strcmp(buf, "help\r\n")) {
            display_help_prompt();
        }
        ++bufferptr;
    }
}