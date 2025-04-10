/*
 * dac_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "config.h"

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
void MX_DAC_Init(DAC_HandleTypeDef * const hdacx)
{
  DAC_ChannelConfTypeDef sConfig = {0};

  hdacx->Instance = DAC;

  /** DAC Initialization
  */
  if (HAL_DAC_Init(hdacx) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT2 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(hdacx, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }



}
