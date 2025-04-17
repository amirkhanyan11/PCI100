/*
 * pex.h
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */

#ifndef DRIVERS_PEX_PEX_H_
#define DRIVERS_PEX_PEX_H_

#include <stdint.h>
#include "main.h"

#define DRIVER_PEX_SLAVE_ADDRESS (0x5E << 1)

#define PEX_CB1_WRITE_REGISTER 0x03
#define PEX_CB1_READ_REGISTER 0x04
#define PEX_CB2_TRANSPARENT_PORTS 0x00
#define PEX_CB3_ENABLE_ALL 0xBC

uint8_t pex_write(uint8_t hi2cx, const uint32_t register_addr, const uint32_t val);
uint32_t pex_read(uint8_t hi2cx, const uint32_t register_addr);

#endif /* DRIVERS_PEX_PEX_H_ */
