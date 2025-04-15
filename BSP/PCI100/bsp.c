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

ADC_HandleTypeDef hadc1;
DAC_HandleTypeDef hdac;
I2C_HandleTypeDef hi2c1;
SPI_HandleTypeDef hspi2;
UART_HandleTypeDef huart1;

static pci100_bsp_t bsp = {
	.hdacx = &hdac,
	.hadcx = &hadc1,
	.huartx = &huart1,
	.hi2cx = &hi2c1,
	.hspix = &hspi2
};

const gpio_info_t gpio_table[] = {
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


//const struct AdcInfo adc_table[] = {
//	{VMON, ADC1, CH1, GPIO_OUTPUT_PP},
//	{0, 0, 0, 0}
//};

void bsp_init(void)
{
	/* START SET GPIO PINS CONFIGS */

	/* END SET GPIO PINS CONFIGS */
	gpio_init();

	dma_init();

	i2c_init(bsp.hi2cx, I2C1, I2C_SPEED_100KHZ, I2C_ADDRESS_7BIT);

	uart_init(bsp.huartx, USART1 ,UART_BAUD_RATE_115200, UART_STOPBIT_1);

	spi_init(bsp.hspix, SPI2, SPI_DATA_8BIT, SPI_CLK_POLARITY_LOW, SPI_CLK_PHASE_1EDGE, SPI_BAUD_RATE_2);

	dac_init(bsp.hdacx, DAC);

	/* START INIT DAC CHANNELS*/

	dac_channel_init(bsp.hdacx, DAC_CHNL_2);

	/* END INIT DAC CHANNELS*/

	adc_init(bsp.hadcx, ADC1, ADC_CLOCK_SYNC_2, ADC_RES_12B);

	/* START INIT ADC CHANNELS*/

	adc_channel_init(bsp.hadcx, ADC_CHNL_10);

	/* END INIT ADC CHANNELS*/
}

pci100_bsp_t *bsp_get(void)
{
	return &bsp;
}
