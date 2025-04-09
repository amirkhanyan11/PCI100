/*
 * chain.c
 *
 *  Created on: Apr 9, 2025
 *      Author: artyom
 */

#include "chain.h"
#include <stdarg.h>
#include <unistd.h>

void chain_init(chain_t *const chain) {
	chain->end = 0;
	chain->pos = 0;
}

uint8_t chain_add(chain_t *const chain, chain_fn_t fn) {
	if (chain->end == CHAIN_MAX_FN_COUNT) {
		return -1;
	}
	chain->container[chain->end] = fn;
	chain->end += 1;
	return 0;
}

uint8_t __attribute__((sentinel)) chain_add_many(chain_t *const chain, chain_fn_t first,  ...)
{
	va_list list;
	va_start(list, first);

	if (-1 == chain_add(chain, first)) {
		return -1;
	}

	chain_fn_t f = NULL;

	while ((f = va_arg(list, chain_fn_t)) != NULL) {
		if (-1 == chain_add(chain, f)) {
			return -1;
		}
	}
	return 0;
}

uint8_t chain_pop(chain_t *const chain) {
	if (chain_is_empty(chain)) {
		return -1;
	}
	chain->end -= 1;
	return 0;
}

chain_fn_t chain_get_next(chain_t *const chain) {
	if (chain_is_empty(chain)) {
		return NULL;
	}
	const chain_fn_t res = chain->container[chain->pos];
	chain->pos += 1;
	return res;
}

bool chain_is_empty(chain_t *const chain) {
	return (chain->pos >= chain->end);
}

