/*
 * spi.c
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#include "spi.h"

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;

static SPI_HandleTypeDef * spi[] = {&hspi1, &hspi2, &hspi3};

static void chip_select(bool mod)
{
	if (mod) {
		gpio_pin_set(SPI_CS, OFF);
	} else {
		gpio_pin_set(SPI_CS, ON);
	}
	HAL_Delay(1);
}

static void write_handler(bool mod, uint8_t hspix)
{
	uint8_t wr_mod = mod ? SPI_WREN : SPI_WRDI;

    chip_select(true);
    HAL_SPI_Transmit(spi[hspix], &wr_mod, 1, 100);
    chip_select(false);
}


uint8_t spi_write(uint8_t hspix, uint16_t address, uint8_t data)
{
    uint8_t txArr[SPI_SIZE] = {SPI_WRITE, address >> 8, address, data};

    write_handler(true, hspix);
    chip_select(true);

    uint8_t status = HAL_SPI_Transmit(spi[hspix], txArr, SPI_SIZE, 1000);

    chip_select(false);
    write_handler(true, hspix);
    return status;
}

uint8_t spi_read(uint8_t hspix, uint16_t address, uint8_t *data)
{
	uint8_t rxArr[SPI_SIZE] = {0};
	uint8_t txArr[SPI_SIZE] = {SPI_READ, address >> 8, address, 0};

	chip_select(true);

    uint8_t status  = HAL_SPI_TransmitReceive(spi[hspix], txArr, rxArr, SPI_SIZE, 1000);

    chip_select(false);
    *data = rxArr[SPI_SIZE - 1];
    return status;
}

uint8_t spi_read_bulk(uint8_t hspix, uint16_t address, uint8_t size, uint8_t *data)
{
	if (size == 0){
		return -1;
	}

	uint8_t rxArr[SPI_SIZE + size];
	uint8_t txArr[SPI_SIZE] = {SPI_READ, address >> 8, address, 0};

	chip_select(true);

	uint8_t status = HAL_SPI_TransmitReceive(spi[hspix], txArr, rxArr, SPI_SIZE + size, 1000);

	if (status == HAL_OK) {

		for (uint8_t i = SPI_SIZE - 1, j = 0; i < SPI_SIZE + size - 1; ++i, ++j) {
			data[j] = rxArr[i];
		}
	}

	chip_select(false);
	return status;
}
