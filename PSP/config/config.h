/*
 * config.h
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#ifndef SRC_CONFIG_CONFIG_H_
#define SRC_CONFIG_CONFIG_H_

#define GPIO_PIN_COUNT 48
#define GPIO_PORT_COUNT 3
#define GPIO_PINS_IN_PORT 16

#include "main.h"

typedef enum e_user_label user_label_e;
typedef enum e_gpio_pin_mode gpio_pin_mode_e;
typedef enum e_gpio_pull_mode gpio_pull_mode_e;
typedef enum e_gpio_mode gpio_mode_e;
typedef enum e_gpio_ports gpio_ports_e;
typedef struct gpio_mode_s gpio_mode_t;
typedef struct gpio_info_s gpio_info_t;
typedef struct chnl_info_s chnl_info_t;


enum {
	ADC1_HANDLER = 1,
	ADC2_HANDLER
};

enum {
	DAC_HANDLER = 1,
};

enum {
	I2C1_HANDLER,
	I2C2_HANDLER,
	I2C3_HANDLER,
};

enum {
	SPI1_HANDLER,
	SPI2_HANDLER,
	SPI3_HANDLER,
};

enum {
	USART1_HANDLER,
	USART2_HANDLER,
	USART3_HANDLER,
};

// SPI configs
enum {
	SPI_CLK_POLARITY_LOW = SPI_POLARITY_LOW,
	SPI_CLK_POLARITY_HIGH = SPI_POLARITY_HIGH,

	SPI_CLK_PHASE_1EDGE = SPI_PHASE_1EDGE,
	SPI_CLK_PHASE_2EDGE = SPI_PHASE_2EDGE,

	SPI_DATA_4BIT = SPI_DATASIZE_4BIT,
	SPI_DATA_5BIT = SPI_DATASIZE_5BIT,
	SPI_DATA_6BIT = SPI_DATASIZE_6BIT,
	SPI_DATA_7BIT = SPI_DATASIZE_7BIT,
	SPI_DATA_8BIT = SPI_DATASIZE_8BIT,
	SPI_DATA_9BIT = SPI_DATASIZE_9BIT,
	SPI_DATA_10BIT = SPI_DATASIZE_10BIT,
	SPI_DATA_11BIT = SPI_DATASIZE_11BIT,
	SPI_DATA_12BIT = SPI_DATASIZE_12BIT,
	SPI_DATA_13BIT = SPI_DATASIZE_13BIT,
	SPI_DATA_14BIT = SPI_DATASIZE_14BIT,
	SPI_DATA_15BIT = SPI_DATASIZE_15BIT,
	SPI_DATA_16BIT = SPI_DATASIZE_16BIT,

	SPI_BAUD_RATE_2 = SPI_BAUDRATEPRESCALER_2,
	SPI_BAUD_RATE_4 = SPI_BAUDRATEPRESCALER_4,
	SPI_BAUD_RATE_8 = SPI_BAUDRATEPRESCALER_8,
	SPI_BAUD_RATE_16 = SPI_BAUDRATEPRESCALER_16,
	SPI_BAUD_RATE_32 = SPI_BAUDRATEPRESCALER_32,
	SPI_BAUD_RATE_64 = SPI_BAUDRATEPRESCALER_64,
	SPI_BAUD_RATE_128 = SPI_BAUDRATEPRESCALER_128,
	SPI_BAUD_RATE_256 = SPI_BAUDRATEPRESCALER_256,

};

// UART configs
enum {
	UART_BAUD_RATE_4800 = 4800,
	UART_BAUD_RATE_9600 = 9600,
	UART_BAUD_RATE_19200 = 19200,
	UART_BAUD_RATE_38400 = 38400,
	UART_BAUD_RATE_57600 = 57600,
	UART_BAUD_RATE_115200 = 115200,


	UART_STOPBIT_0_5 = UART_STOPBITS_0_5,
	UART_STOPBIT_1 = UART_STOPBITS_1,
	UART_STOPBIT_1_5 = UART_STOPBITS_1_5,
	UART_STOPBIT_2 = UART_STOPBITS_2,

};

// I2C configs
enum {
	I2C_SPEED_100KHZ = 0x00303D5B,
	I2C_SPEED_90KHZ = 0x00303D6D,
	I2C_SPEED_80KHZ = 0x00304779,
	I2C_SPEED_70KHZ = 0x00303DA0,
	I2C_SPEED_60KHZ = 0x00303DC6,
	I2C_SPEED_50KHZ = 0x00303DFB,
	I2C_SPEED_40KHZ = 0x00308FF9,
	I2C_SPEED_30KHZ = 0x10101EE8,
	I2C_SPEED_20KHZ = 0x101098F3,
	I2C_SPEED_10KHZ = 0x40003EFF,

	I2C_ADDRESS_7BIT = I2C_ADDRESSINGMODE_7BIT,
	I2C_ADDRESS_10BIT = I2C_ADDRESSINGMODE_10BIT,
};

// ADC configs
enum {
	ADC_CLOCK_SYNC_2 = ADC_CLOCK_SYNC_PCLK_DIV2,
	ADC_CLOCK_SYNC_4 = ADC_CLOCK_SYNC_PCLK_DIV4,
	ADC_CLOCK_SYNC_6 = ADC_CLOCK_SYNC_PCLK_DIV6,
	ADC_CLOCK_SYNC_8 = ADC_CLOCK_SYNC_PCLK_DIV8,

	ADC_RES_12B = ADC_RESOLUTION_12B,
	ADC_RES_10B = ADC_RESOLUTION_10B,
	ADC_RES_8B = ADC_RESOLUTION_8B,
	ADC_RES_6B = ADC_RESOLUTION_6B,

	ADC_CHNL_1 = ADC_CHANNEL_1,
	ADC_CHNL_2 = ADC_CHANNEL_2,
	ADC_CHNL_3 = ADC_CHANNEL_3,
	ADC_CHNL_4 = ADC_CHANNEL_4,
	ADC_CHNL_5 = ADC_CHANNEL_5,
	ADC_CHNL_6 = ADC_CHANNEL_6,
	ADC_CHNL_7 = ADC_CHANNEL_7,
	ADC_CHNL_8 = ADC_CHANNEL_8,
	ADC_CHNL_9 = ADC_CHANNEL_9,
	ADC_CHNL_10 = ADC_CHANNEL_10,
	ADC_CHNL_11 = ADC_CHANNEL_11,
	ADC_CHNL_12 = ADC_CHANNEL_12,
	ADC_CHNL_13 = ADC_CHANNEL_13,
	ADC_CHNL_14 = ADC_CHANNEL_14,
	ADC_CHNL_15 = ADC_CHANNEL_15,
	ADC_CHNL_16 = ADC_CHANNEL_16,
	ADC_CHNL_17 = ADC_CHANNEL_17,
	ADC_CHNL_18 = ADC_CHANNEL_18,
};

// DAC configs
enum {
	DAC_CHNL_1 = DAC_CHANNEL_1,
	DAC_CHNL_2 = DAC_CHANNEL_2,
};

enum e_gpio_ports{
	GPIO_PORT_A,
	GPIO_PORT_B,
	GPIO_PORT_C,
};

enum {
	PIN_0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8,
	PIN_9,
	PIN_10,
	PIN_11,
	PIN_12,
	PIN_13,
	PIN_14,
	PIN_15,
};

enum e_gpio_mode{
	GPIO_INPUT = GPIO_MODE_INPUT,
	GPIO_OUTPUT_PP = GPIO_MODE_OUTPUT_PP,
	GPIO_OUTPUT_OD = GPIO_MODE_OUTPUT_OD,
	GPIO_AF_PP = GPIO_MODE_AF_PP,
	GPIO_AF_OD = GPIO_MODE_AF_OD,

	GPIO_IT_RISING = GPIO_MODE_IT_RISING,
	GPIO_IT_FALLING = GPIO_MODE_IT_FALLING,
	GPIO_IT_RISING_FALLING = GPIO_MODE_IT_RISING_FALLING,

	GPIO_ANALOG = GPIO_MODE_ANALOG,
	GPIO_EVT_RISING = GPIO_MODE_EVT_RISING,
	GPIO_EVT_FALLING = GPIO_MODE_EVT_FALLING,
	GPIO_EVT_RISING_FALLING = GPIO_MODE_EVT_RISING_FALLING,
};

enum e_gpio_pull_mode {
	NOPULL = GPIO_NOPULL,
	PULLUP = GPIO_PULLUP,
	PULLDOWN = GPIO_PULLDOWN,
};

enum e_gpio_pin_mode {
	OFF,
	ON,
};


enum e_user_label{
	DEFAULT = 0,
	PCI_RESET,
	PG,
	LED_CONFIG1,
	LED_CONFIG2,
	LED_CONFIG3,
	LED_CONFIG4,
	LED_CONFIG5,
	LED_CONFIG6,
	LED,
	SPI_CS,
	DAC_EXIT,
	PCIE_PERST,
};

struct gpio_info_s {
	user_label_e	user_label;
	gpio_ports_e	port;
	uint16_t		pin;
	gpio_mode_e		mode;
};

struct chnl_info_s {
	uint8_t			typedef_handler;
	uint8_t 		*chnl_table;
};

void spi_init(
		uint8_t instance,
		uint32_t data_size,
		uint32_t clk_polarity,
		uint32_t clk_phase,
		uint32_t baud_rate_prescaler
		);

void dma_init(void);

void i2c_init(
		uint8_t instance,
		uint32_t timing,
		uint32_t address_mode
		);

void uart_init(
		uint8_t instance,
		uint32_t baud_rate,
		uint32_t stop_bits);

void adc_init(
		const chnl_info_t *table,
		uint32_t clock_prescaler,
		uint32_t resolution
		);


void dac_init(const chnl_info_t *table);

void			gpio_init(const gpio_info_t *table);
gpio_pin_mode_e	gpio_pin_get(user_label_e label);
void			gpio_pin_set(user_label_e label, gpio_pin_mode_e mode);
void 			gpio_set(const user_label_e label, const uint8_t port, const uint8_t pin, const gpio_mode_e mode);


#endif /* SRC_CONFIG_CONFIG_H_ */
