/*
 * gpio_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "config.h"

static uint8_t gpio_get_index(GPIO_TypeDef * const port, uint16_t pin);
static uint8_t gpio_get_index_by_label(user_label_e label);
static void _gpio_set(user_label_e label, GPIO_TypeDef * const port, uint16_t pin, gpio_mode_e mode, uint8_t index);

static struct {

	GPIO_TypeDef	*port;
	uint16_t		pin;
	user_label_e	user_label;
	gpio_mode_t		mode;


} gpio_table[GPIO_PIN_COUNT];

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

	uint16_t pin = 0;
	GPIO_TypeDef *ports[] = {GPIOA, GPIOB, GPIOC};
	for (uint8_t i = 0, j = -1; i < GPIO_PIN_COUNT; ++i) {
		if (i % GPIO_PINS_IN_PORT == 0) {
			j += 1;
			pin |= 1;
		}
		_gpio_set(DEFAULT, ports[j], pin, GPIO_INPUT, i);
		pin <<= 1;
	}
}


void gpio_set(user_label_e label, GPIO_TypeDef * const port, uint16_t pin, gpio_mode_e mode)
{
	if (label == DEFAULT) {
		return ;
	}

	uint8_t pin_index = gpio_get_index(port, pin);

	if (pin_index == -1) {
		return ;
	}

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	gpio_table[pin_index].user_label = label;
	GPIO_InitStruct.Mode = gpio_table[pin_index].mode.mode = mode;
	GPIO_InitStruct.Pull = gpio_table[pin_index].mode.pull_mode;
	GPIO_InitStruct.Pin = gpio_table[pin_index].pin;

	if (mode == GPIO_OUTPUT_OD || mode == GPIO_OUTPUT_PP) {
		HAL_GPIO_WritePin(port, pin, OFF);
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	}

	HAL_GPIO_Init(gpio_table[pin_index].port, &GPIO_InitStruct);
}



void gpio_pin_set(user_label_e label, gpio_pin_mode_e mode)
{
	uint8_t index = gpio_get_index_by_label(label);
	if (index == -1) {
		return ;
	}

	HAL_GPIO_WritePin(gpio_table[index].port, gpio_table[index].pin, mode);
}


gpio_pin_mode_e gpio_pin_get(user_label_e label)
{
	uint8_t index = gpio_get_index_by_label(label);
	if (index == -1) {
		return -1;
	}

	return HAL_GPIO_ReadPin(gpio_table[index].port, gpio_table[index].pin);
}


static void _gpio_set(user_label_e label, GPIO_TypeDef * const port, uint16_t pin, gpio_mode_e mode, uint8_t index)
{
	gpio_table[index].user_label = label;
	gpio_table[index].port = port;
	gpio_table[index].pin = pin;
	gpio_table[index].mode.mode = mode;
	gpio_table[index].mode.pull_mode = PULLUP;
}


static uint8_t gpio_get_index(GPIO_TypeDef * const port, uint16_t pin)
{
	uint8_t i = 0;

	for (; i < GPIO_PIN_COUNT; i += GPIO_PINS_IN_PORT){
		if (gpio_table[i].port == port) {
			break ;
		}
	}

	for (; i < GPIO_PIN_COUNT; ++i) {
		if (gpio_table[i].pin == pin) {
			return i;
		}
	}
	return -1;
}


static uint8_t gpio_get_index_by_label(user_label_e label)
{
	for (uint8_t i = 0; i < GPIO_PIN_COUNT; ++i) {
		if (gpio_table[i].user_label == label) {
			return i;
		}
	}
	return -1;
}
