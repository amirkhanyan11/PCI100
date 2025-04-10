/*
 * uart_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */


#include "config.h"

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void uart_init(UART_HandleTypeDef * const huartx, USART_TypeDef * const instance, uint32_t baud_rate, uint32_t stop_bits)
{

	huartx->Instance = instance;
	huartx->Init.BaudRate = baud_rate;
	huartx->Init.StopBits = stop_bits;
	huartx->Init.WordLength = UART_WORDLENGTH_8B;
	huartx->Init.Mode = UART_MODE_TX_RX;
	huartx->Init.Parity = UART_PARITY_NONE;
	huartx->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huartx->Init.OverSampling = UART_OVERSAMPLING_16;
	huartx->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huartx->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	if (HAL_UART_Init(huartx) != HAL_OK)
	{
		Error_Handler();
	}

}
