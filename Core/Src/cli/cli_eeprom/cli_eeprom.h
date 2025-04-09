/*
 * cli_eeprom.h
 *
 *  Created on: Apr 9, 2025
 *      Author: Tigran
 */

#ifndef SRC_CLI_CLI_EEPROM_CLI_EEPROM_H_
#define SRC_CLI_CLI_EEPROM_CLI_EEPROM_H_

#define EEPROM_READ_MAX_SIZE 1024

#include "cli.h"

uint8_t cli_eeprom(cmd_t * const cmd);
uint8_t __eeprom_err(const char * const cmd, const char * const s);

// middlewares
uint8_t cli_eeprom_write_middleware(cmd_t * const cmd, chain_t *const chain);
uint8_t cli_eeprom_read_middleware(cmd_t * const cmd, chain_t *const chain);
uint8_t cli_eeprom_read_bulk_middleware(cmd_t * const cmd, chain_t *const chain);

#endif /* SRC_CLI_CLI_EEPROM_CLI_EEPROM_H_ */
