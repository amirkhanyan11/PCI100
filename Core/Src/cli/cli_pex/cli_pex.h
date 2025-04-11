/*
 * cli_pex.h
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */

#ifndef SRC_CLI_CLI_PEX_CLI_PEX_H_
#define SRC_CLI_CLI_PEX_CLI_PEX_H_


#include "pex.h"
#include "cmd.h"
#include "cli_string_literals.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "bsp.h"
#include "cli_pex.h"

#include "cmd.h"
#include "cli.h"

uint8_t cli_pex(cmd_t * const cmd);

uint8_t __pex_err(const char * const cmd, const char * const option, const char * const s);

// middlewares
uint8_t cli_pex_write_middleware(cmd_t * const cmd, chain_t *const chain);
uint8_t cli_pex_read_middleware(cmd_t * const cmd, chain_t * const chain);


#endif /* SRC_CLI_CLI_PEX_CLI_PEX_H_ */
