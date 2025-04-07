/*
 * pex.h
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#ifndef SRC_PEX_PEX_H_
#define SRC_PEX_PEX_H_

#include "../cmd/cmd.h"

#define PEX_SLAVE_ADDRESS (0x5E << 1)

#define PEX_CB1_WRITE_REGISTER 0x03
#define PEX_CB1_READ_REGISTER 0x04
#define PEX_CB2_TRANSPARENT_PORTS 0x00
#define PEX_CB3_ENABLE_ALL 0xBC

uint8_t exec_pex(cmd_t * const cmd);
uint8_t pex_write(cmd_t * const cmd);
uint8_t pex_read(cmd_t * const cmd);
uint8_t pex_help(void);

#endif /* SRC_PEX_PEX_H_ */
