/*
 * gpio_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "config.h"

static uint16_t _get_pin(const uint8_t pin_id);
static uint8_t gpio_get_index(user_label_e label);
extern const gpio_info_t *gpio_table;
static GPIO_TypeDef * ports[] = {GPIOA, GPIOB, GPIOC};

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

	for (uint8_t i = 0; gpio_table[i].user_label != DEFAULT; ++i) {
		GPIO_InitStruct.Mode = gpio_table[i].mode;
		GPIO_InitStruct.Pull = PULLUP;
		GPIO_InitStruct.Pin = _get_pin(gpio_table[i].pin);

		if (GPIO_InitStruct.Mode == GPIO_OUTPUT_OD || GPIO_InitStruct.Mode == GPIO_OUTPUT_PP) {
			HAL_GPIO_WritePin(ports[gpio_table[i].port], gpio_table[i].pin, OFF);
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		}

		HAL_GPIO_Init(ports[gpio_table[i].port], &GPIO_InitStruct);
	}
}



void gpio_pin_set(user_label_e label, gpio_pin_mode_e mode)
{
	uint8_t index = gpio_get_index(label);
	if (index == -1) {
		return ;
	}

	HAL_GPIO_WritePin(ports[gpio_table[index].port], gpio_table[index].pin, mode);
}


gpio_pin_mode_e gpio_pin_get(user_label_e label)
{
	uint8_t index = gpio_get_index(label);
	if (index == -1) {
		return -1;
	}

	return HAL_GPIO_ReadPin(ports[gpio_table[index].port], gpio_table[index].pin);
}

static uint8_t gpio_get_index(user_label_e label)
{
	for (uint8_t i = 0; gpio_table[i].user_label != DEFAULT; ++i) {
		if (gpio_table[i].user_label == label) {
			return i;
		}
	}
	return -1;
}

static uint16_t _get_pin(const uint8_t pin_id)
{
	return GPIO_PIN_0 << pin_id;;
}
