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

uint8_t exec_pex(cmd_t * const cmd);
uint8_t pex_write(cmd_t * const cmd);
uint8_t pex_read(cmd_t * const cmd);

#endif /* SRC_PEX_PEX_H_ */
