/*
 * gpio_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "config.h"

static uint8_t gpio_get_index(user_label_e label);

static struct {

	GPIO_TypeDef	*port;
	uint16_t		pin;
	user_label_e	user_label;
	gpio_mode_t		mode;


} gpio_table[GPIO_PIN_COUNT];
static GPIO_TypeDef * ports[] = {GPIOA, GPIOB, GPIOC};
static uint8_t gpio_table_size;

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void gpio_init(void)
{
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	for (uint8_t i = 0; i < gpio_table_size; ++i) {
		GPIO_InitStruct.Mode = gpio_table[i].mode.mode;
		GPIO_InitStruct.Pull = gpio_table[i].mode.pull_mode;
		GPIO_InitStruct.Pin = gpio_table[i].pin;

		if (GPIO_InitStruct.Mode == GPIO_OUTPUT_OD || GPIO_InitStruct.Mode == GPIO_OUTPUT_PP) {
			HAL_GPIO_WritePin(gpio_table[i].port, gpio_table[i].pin, OFF);
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		}

		HAL_GPIO_Init(gpio_table[i].port, &GPIO_InitStruct);
	}
}

static uint16_t _get_pin(const uint8_t pin_id)
{
	uint16_t pin = GPIO_PIN_0;
	for (uint8_t i = 0; i < pin_id; ++i) {
		pin <<= 1;
	}

	return pin;
}

void gpio_set(const user_label_e label, const uint8_t port, const uint8_t pin, const gpio_mode_e mode)
{
	if (label == DEFAULT || gpio_table_size >= GPIO_PIN_COUNT || pin >= GPIO_PINS_IN_PORT) {
		return ;
	}

	gpio_table[gpio_table_size].port = ports[port];
	gpio_table[gpio_table_size].pin = _get_pin(pin);
	gpio_table[gpio_table_size].user_label = label;
	gpio_table[gpio_table_size].mode.mode = mode;
	gpio_table[gpio_table_size].mode.pull_mode = PULLUP;

	gpio_table_size += 1;
}



void gpio_pin_set(user_label_e label, gpio_pin_mode_e mode)
{
	uint8_t index = gpio_get_index(label);
	if (index == -1) {
		return ;
	}

	HAL_GPIO_WritePin(gpio_table[index].port, gpio_table[index].pin, mode);
}


gpio_pin_mode_e gpio_pin_get(user_label_e label)
{
	uint8_t index = gpio_get_index(label);
	if (index == -1) {
		return -1;
	}

	return HAL_GPIO_ReadPin(gpio_table[index].port, gpio_table[index].pin);
}

static uint8_t gpio_get_index(user_label_e label)
{
	for (uint8_t i = 0; i < gpio_table_size; ++i) {
		if (gpio_table[i].user_label == label) {
			return i;
		}
	}
	return -1;
}
