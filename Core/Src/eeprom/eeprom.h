#ifndef SPI_H
# define SPI_H

#include "../utils/utils.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "typedefs.h"
#include "../cmd/cmd.h"

#define SPI_SIZE 4
#define SPI_READ 0x3
#define SPI_WRITE 0x2
#define SPI_WREN 0x6
#define SPI_WRDI 0x4

void Eeprom_read_status_reg(void);

uint8_t exec_eeprom(cmd_t * const cmd);

#endif // SPI_H
