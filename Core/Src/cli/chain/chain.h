/*
 * chain.h
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */

#ifndef SRC_CLI_CHAIN_CHAIN_H_
#define SRC_CLI_CHAIN_CHAIN_H_

#define CHAIN_MAX_FN_COUNT 8

#include "typedefs.h"
#include <stdbool.h>

struct chain_s
{
	chain_fn_t container[CHAIN_MAX_FN_COUNT];
	uint8_t end;
	uint8_t pos;
};


void chain_init(chain_t *const chain);
bool chain_is_empty(chain_t *const chain);
chain_fn_t chain_get_next(chain_t *const chain);
uint8_t chain_add(chain_t *const chain, chain_fn_t fn);
uint8_t chain_pop(chain_t *const chain);

uint8_t __attribute__((sentinel)) chain_add_many(chain_t *const chain, chain_fn_t first,  ...);

#endif /* SRC_CLI_CHAIN_CHAIN_H_ */
