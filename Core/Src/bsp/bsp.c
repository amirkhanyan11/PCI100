/*
 * bsp.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "bsp.h"
#include "typedefs.h"
#include "config.h"

void bsp_config(bsp_t * const bsp,
		DAC_HandleTypeDef *  const hdacx,
		ADC_HandleTypeDef *  const hadcx,
		UART_HandleTypeDef * const huartx,
		I2C_HandleTypeDef * const hi2cx,
		SPI_HandleTypeDef * const hspix
) {

	bsp->hdacx = hdacx;
	bsp->hadcx = hadcx;
	bsp->huartx = huartx;
	bsp->hi2cx = hi2cx;
	bsp->hspix = hspix;

	gpio_init();
	/* START INIT GPIO PINS INITIALIZATION */

	gpio_set(PCI_RESET, GPIOC, GPIO_PIN_2, GPIO_OUTPUT_PP, 0);
	gpio_set(PG, GPIOC, GPIO_PIN_3, GPIO_INPUT, 0);
	gpio_set(LED_CONFIG1, GPIOA, GPIO_PIN_1, GPIO_INPUT, 0);
	gpio_set(LED_CONFIG2, GPIOA, GPIO_PIN_2, GPIO_INPUT, 0);
	gpio_set(LED_CONFIG3, GPIOA, GPIO_PIN_3, GPIO_INPUT, 0);
	gpio_set(LED_CONFIG4, GPIOA, GPIO_PIN_4, GPIO_INPUT, 0);
	gpio_set(LED_CONFIG5, GPIOA, GPIO_PIN_6, GPIO_INPUT, 0);
	gpio_set(LED_CONFIG6, GPIOA, GPIO_PIN_7, GPIO_INPUT, 0);
	gpio_set(LED, GPIOB, GPIO_PIN_11, GPIO_OUTPUT_PP, 0);
	gpio_set(SPI_CS, GPIOB, GPIO_PIN_12, GPIO_OUTPUT_PP, 0);
	gpio_set(DAC_EXIT, GPIOB, GPIO_PIN_9, GPIO_IT_RISING, 0);
	gpio_set(PCIE_PERST, GPIOB, GPIO_PIN_4, GPIO_INPUT, 0);

	/* END INIT GPIO PINS INITIALIZATION */

	MX_DMA_Init();
	MX_I2C_Init(bsp->hi2cx, I2C_TIMING, I2C_ADDRESS_7BIT);
	MX_USART_UART_Init(bsp->huartx);
	MX_DAC_Init(bsp->hdacx);

	MX_SPI_Init(bsp->hspix, SPI2, SPI_DATA_8BIT, SPI_CLK_POLARITY_LOW, SPI_CLK_PHASE_1EDGE, SPI_BAUD_RATE_2);

	uint32_t adc_channel[] = {ADC_CHANNEL_10, 0};
	MX_ADC_Init(bsp->hadcx, ADC1, ADC_CLOCK_SYNC_2, ADC_RES_12B, adc_channel);

	HAL_DAC_Start(bsp->hdacx, DAC_CHANNEL_2);
}

