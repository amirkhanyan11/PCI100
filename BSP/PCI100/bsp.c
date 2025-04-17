/*
 * bsp.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include <dac.h>
#include "bsp.h"

#include "typedefs.h"
#include "config.h"
#include "adc.h"

static pci100_bsp_t bsp = {
	.hdacx = DAC_HANDLER,
	.hadcx = ADC1_HANDLER,
	.huartx = USART1_HANDLER,
	.hi2cx = I2C1_HANDLER,
	.hspix = SPI2_HANDLER
};

static const gpio_info_t gpio_table[] = {
	{PCI_RESET, GPIO_PORT_C, PIN_2, GPIO_OUTPUT_PP},
	{PG, GPIO_PORT_C, PIN_3, GPIO_INPUT},
	{LED_CONFIG1, GPIO_PORT_A, PIN_1, GPIO_INPUT},
	{LED_CONFIG2, GPIO_PORT_A, PIN_2, GPIO_INPUT},
	{LED_CONFIG3, GPIO_PORT_A, PIN_3, GPIO_INPUT},
	{LED_CONFIG4, GPIO_PORT_A, PIN_4, GPIO_INPUT},
	{LED_CONFIG5, GPIO_PORT_A, PIN_6, GPIO_INPUT},
	{LED_CONFIG6, GPIO_PORT_A, PIN_7, GPIO_INPUT},
	{LED, GPIO_PORT_B, PIN_11, GPIO_OUTPUT_PP},
	{SPI_CS, GPIO_PORT_B, PIN_12, GPIO_OUTPUT_PP},
	{DAC_EXIT, GPIO_PORT_B, PIN_9, GPIO_IT_RISING},
	{PCIE_PERST, GPIO_PORT_B, PIN_4, GPIO_INPUT},
	{0, 0, 0, 0}
};

static uint8_t adc1_chnl_table[] = {ADC_CHNL_10, 0};

static const chnl_info_t adc1_table[] = {
	{ADC1_HANDLER, adc1_chnl_table},
	{0, 0}
};

static uint8_t dac_chnl_table[] = {DAC_CHNL_2, 0};

static const chnl_info_t dac_table[] = {
	{DAC_HANDLER, dac_chnl_table},
	{0, 0}
};

void bsp_init(void)
{
	gpio_init(gpio_table);

	dma_init();

	i2c_init(bsp.hi2cx, I2C_SPEED_100KHZ, I2C_ADDRESS_7BIT);

	uart_init(bsp.huartx, UART_BAUD_RATE_115200, UART_STOPBIT_1);

	spi_init(bsp.hspix, SPI_DATA_8BIT, SPI_CLK_POLARITY_LOW, SPI_CLK_PHASE_1EDGE, SPI_BAUD_RATE_2);

	dac_init(dac_table);

	adc_init(adc1_table, ADC_CLOCK_SYNC_2, ADC_RES_12B);
}

pci100_bsp_t *bsp_get(void)
{
	return &bsp;
}
