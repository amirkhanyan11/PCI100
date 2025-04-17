/*
 * uart_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */


#include "config.h"

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

static USART_TypeDef * instance_table[] = {USART1, USART2, USART3};

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void uart_init(uint8_t instance, uint32_t baud_rate, uint32_t stop_bits)
{

	huart1.Instance = instance_table[instance];
	huart1.Init.BaudRate = baud_rate;
	huart1.Init.StopBits = stop_bits;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		error_handler();
	}

}
