/*
 * filo.h
 *
 *  Created on: Apr 1, 2025
 *      Author: artyom
 */

#ifndef SRC_FILO_FILO_H_
#define SRC_FILO_FILO_H_

#include <stdint.h>
#include "typedefs.h"

#define FILO_BUFFER_SIZE 256

struct filo_s
{
	char buffer[FILO_BUFFER_SIZE];
	uint32_t end;
};


void 	filo_init(filo_t *filo);
char 	filo_get(filo_t *filo);
uint8_t filo_set(filo_t *filo, const char c);
uint8_t filo_is_empty(filo_t *filo);
void 	filo_reset(filo_t *filo);


#endif /* SRC_FILO_FILO_H_ */
