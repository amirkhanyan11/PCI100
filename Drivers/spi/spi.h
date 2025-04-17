/*
 * spi.h
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#ifndef DRIVERS_SPI_SPI_H_
#define DRIVERS_SPI_SPI_H_

#define SPI_SIZE 4
#define SPI_READ 0x3
#define SPI_WRITE 0x2
#define SPI_WREN 0x6
#define SPI_WRDI 0x4

#include "main.h"
#include "config.h"
#include <stdbool.h>

uint8_t spi_write(uint8_t hspix, uint16_t address, uint8_t data);
uint8_t spi_read(uint8_t hspix, uint16_t address, uint8_t *data);
uint8_t spi_read_bulk(uint8_t hspix, uint16_t address, uint8_t size, uint8_t *data);


#endif /* DRIVERS_SPI_SPI_H_ */
