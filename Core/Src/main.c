/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <dac.h>
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "led.h"
#include "cli.h"
#include "app.h"
#include "cmd.h"
#include "pex.h"
#include "fifo.h"
#include "psp.h"

#include "../../BSP/PCI100/bsp.h"

app_t app;

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{


	/* Initialize MPU, HAL and Sysclock*/
	psp_init();

	/* Initialize PCI100 and necessary drivers*/
	bsp_init();

	/* Initialize application*/
	app_init(&app);

	/* Configure command line interface*/
	cli_config(&app);

	while (1)
	{
		app_run(&app);
	}

}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
