/*
 * spi.c
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#include "spi.h"

static void chip_select(bool mod)
{
	if (mod) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	}
	HAL_Delay(1);
}

static void write_handler(bool mod, SPI_HandleTypeDef *hspix)
{
	uint8_t wr_mod = mod ? SPI_WREN : SPI_WRDI;

    chip_select(true);
    HAL_SPI_Transmit(hspix, &wr_mod, 1, 100);
    chip_select(false);
}


uint8_t spi_write(SPI_HandleTypeDef *hspix, uint16_t address, uint8_t data)
{
    uint8_t txArr[SPI_SIZE] = {SPI_WRITE, address >> 8, address, data};

    write_handler(true, hspix);
    chip_select(true);

    uint8_t status = HAL_SPI_Transmit(hspix, txArr, SPI_SIZE, 1000);

    chip_select(false);
    write_handler(true, hspix);
    return status;
}

uint8_t spi_read(SPI_HandleTypeDef *hspix, uint16_t address, uint8_t *data)
{
	uint8_t rxArr[SPI_SIZE] = {0};
	uint8_t txArr[SPI_SIZE] = {SPI_READ, address >> 8, address, 0};

	chip_select(true);

    uint8_t status  = HAL_SPI_TransmitReceive(hspix, txArr, rxArr, SPI_SIZE, 1000);

    chip_select(false);
    *data = rxArr[SPI_SIZE - 1];
    return status;
}

uint8_t spi_read_bulk(SPI_HandleTypeDef *hspix, uint16_t address, uint8_t size, uint8_t *data)
{
	if (size == 0){
		return -1;
	}

	uint8_t rxArr[SPI_SIZE + size];
	uint8_t txArr[SPI_SIZE] = {SPI_READ, address >> 8, address, 0};

	chip_select(true);

	uint8_t status = HAL_SPI_TransmitReceive(hspix, txArr, rxArr, SPI_SIZE + size, 1000);

	if (status == HAL_OK) {

		for (uint8_t i = SPI_SIZE - 1, j = 0; i < SPI_SIZE + size - 1; ++i, ++j) {
			data[j] = rxArr[i];
		}
	}

	chip_select(false);
	return status;
}
