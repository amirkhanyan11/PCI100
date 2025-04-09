/*
 * uart_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */


#include "config.h"

#define UART_BAUD_RATE 115200

UART_HandleTypeDef huart1 = {
  .Instance = USART1,
  .Init.BaudRate = UART_BAUD_RATE,
  .Init.WordLength = UART_WORDLENGTH_8B,
  .Init.StopBits = UART_STOPBITS_1,
  .Init.Parity = UART_PARITY_NONE,
  .Init.Mode = UART_MODE_TX_RX,
  .Init.HwFlowCtl = UART_HWCONTROL_NONE,
  .Init.OverSampling = UART_OVERSAMPLING_16,
  .Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE,
  .AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT
};


/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART_UART_Init(UART_HandleTypeDef * const huartx)
{

  if (HAL_UART_Init(huartx) != HAL_OK)
  {
    Error_Handler();
  }

}
