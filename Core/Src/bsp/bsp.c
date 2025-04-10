/*
 * bsp.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "bsp.h"
#include "typedefs.h"
#include "config.h"

void bsp_init(bsp_t * const bsp,
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

	gpio_set(PCI_RESET, GPIOC, GPIO_PIN_2, GPIO_OUTPUT_PP);
	gpio_set(PG, GPIOC, GPIO_PIN_3, GPIO_INPUT);
	gpio_set(LED_CONFIG1, GPIOA, GPIO_PIN_1, GPIO_INPUT);
	gpio_set(LED_CONFIG2, GPIOA, GPIO_PIN_2, GPIO_INPUT);
	gpio_set(LED_CONFIG3, GPIOA, GPIO_PIN_3, GPIO_INPUT);
	gpio_set(LED_CONFIG4, GPIOA, GPIO_PIN_4, GPIO_INPUT);
	gpio_set(LED_CONFIG5, GPIOA, GPIO_PIN_6, GPIO_INPUT);
	gpio_set(LED_CONFIG6, GPIOA, GPIO_PIN_7, GPIO_INPUT);
	gpio_set(LED, GPIOB, GPIO_PIN_11, GPIO_OUTPUT_PP);
	gpio_set(SPI_CS, GPIOB, GPIO_PIN_12, GPIO_OUTPUT_PP);
	gpio_set(DAC_EXIT, GPIOB, GPIO_PIN_9, GPIO_IT_RISING);
	gpio_set(PCIE_PERST, GPIOB, GPIO_PIN_4, GPIO_INPUT);

	/* END INIT GPIO PINS INITIALIZATION */

	dma_init();

	i2c_init(bsp->hi2cx, I2C1, I2C_TIMING, I2C_ADDRESS_7BIT);

	uart_init(bsp->huartx, USART1 ,UART_BAUD_RATE_115200, UART_STOPBIT_1);

	dac_init(bsp->hdacx, DAC);

	spi_init(bsp->hspix, SPI2, SPI_DATA_8BIT, SPI_CLK_POLARITY_LOW, SPI_CLK_PHASE_1EDGE, SPI_BAUD_RATE_2);

	uint32_t adc_channel[] = {ADC_CHANNEL_10, 0};
	adc_init(bsp->hadcx, ADC1, ADC_CLOCK_SYNC_2, ADC_RES_12B, adc_channel);


}

