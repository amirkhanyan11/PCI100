/*
 * gpio_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "config.h"


struct {

	GPIO_TypeDef	*port;
	uint16_t		pin;
	user_label_e	user_label;
	gpio_mode_t		mode;


} gpio_table[GPIO_PIN_COUNT];

//
//{LED1, PORTB, 11, OUTPUT, FALSE}
//
//gpio_set(LED1, ON)
//gpio_get(LED1);


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
//void MX_GPIO_Init(void)
//{
//  GPIO_InitTypeDef GPIO_InitStruct = {0};



  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOB, MCU_ACT_LED_Pin|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC2 */
//  GPIO_InitStruct.Pin = GPIO_PIN_2;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//  gpio_set(PCI_RESET, GPIOC, GPIO_PIN_2, GPIO_OUTPUT_PP, 0);
  /*Configure GPIO pin : PC3 */
//  GPIO_InitStruct.Pin = GPIO_PIN_3;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//  gpio_set(PG, GPIOC, GPIO_PIN_3, GPIO_INPUT, 0);
  /*Configure GPIO pins : PA1 PA2 PA3 PA6
                           PA7 */
//  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6
//                          |GPIO_PIN_7;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//  gpio_set(LED_CONFIG1, GPIOA, GPIO_PIN_1, GPIO_INPUT, 0);
//  gpio_set(LED_CONFIG2, GPIOA, GPIO_PIN_2, GPIO_INPUT, 0);
//  gpio_set(LED_CONFIG3, GPIOA, GPIO_PIN_3, GPIO_INPUT, 0);
//  gpio_set(LED_CONFIG4, GPIOA, GPIO_PIN_4, GPIO_INPUT, 0);
//  gpio_set(LED_CONFIG5, GPIOA, GPIO_PIN_6, GPIO_INPUT, 0);
//  gpio_set(LED_CONFIG6, GPIOA, GPIO_PIN_7, GPIO_INPUT, 0);

  /*Configure GPIO pin : PA4 */
//  GPIO_InitStruct.Pin = GPIO_PIN_4;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : MCU_ACT_LED_Pin */
//  GPIO_InitStruct.Pin = MCU_ACT_LED_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(MCU_ACT_LED_GPIO_Port, &GPIO_InitStruct);
//  gpio_set(LED, GPIOB, GPIO_PIN_11, GPIO_OUTPUT_PP, 0);

  /*Configure GPIO pin : PB12 */
//  GPIO_InitStruct.Pin = GPIO_PIN_12;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//  gpio_set(SPI_CS, GPIOB, GPIO_PIN_12, GPIO_OUTPUT_PP, 0);

  /*Configure GPIO pin : PC9 */
//  GPIO_InitStruct.Pin = GPIO_PIN_9;
//  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//  gpio_set(DAC_EXIT, GPIOB, GPIO_PIN_9, GPIO_IT_RISING, 0);

  /*Configure GPIO pin : PB4 */
//  GPIO_InitStruct.Pin = GPIO_PIN_4;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//  gpio_set(PCIE_PERST, GPIOB, GPIO_PIN_4, GPIO_INPUT, 0);

//}


static uint8_t gpio_get_index(GPIO_TypeDef *port, uint16_t pin)
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

void gpio_set(user_label_e label, GPIO_TypeDef *port, uint16_t pin, gpio_mode_e mode, uint8_t index)
{
	if (label != DEFAULT)
	{
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

	} else {
		gpio_table[index].user_label = label;
		gpio_table[index].port = port;
		gpio_table[index].pin = pin;
		gpio_table[index].mode.pull_mode = PULLUP;
	}
}

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
		gpio_set(DEFAULT, ports[j], pin, GPIO_INPUT, i);
		pin <<= 1;
	}
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
