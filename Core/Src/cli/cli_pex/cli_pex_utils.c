/*
 * cli_pex_utils.c
 *
 *  Created on: Apr 11, 2025
 *      Author: Tigran
 */

#include "cli_pex.h"

uint8_t __pex_err(const char * const cmd, const char * const option, const char * const s)
{
	printf("pex: %s: %s\r\n", cmd, option);
	printchunk("Usage:", s, NULL);
	return EINVAL;
}
