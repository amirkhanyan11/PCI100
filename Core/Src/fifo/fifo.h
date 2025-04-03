/*
 * fifo.h
 *
 *  Created on: Apr 1, 2025
 *      Author: artyom
 */

#ifndef SRC_FIFO_FIFO_H_
#define SRC_FIFO_FIFO_H_

#define FIFO_BUFFER_SIZE 4096

#include <stdint.h>
#include "typedefs.h"

struct fifo_s
{
	char buffer[FIFO_BUFFER_SIZE];
	uint32_t pos;
	uint32_t end;
};


void fifo_init(fifo_t *fifo);
char fifo_get(fifo_t *fifo);
void fifo_reset(fifo_t *fifo);
void fifo_set(fifo_t *fifo, const char c);
uint8_t fifo_is_empty(fifo_t *fifo);
void fifo_unshift(fifo_t *fifo);

#endif /* SRC_FIFO_FIFO_H_ */
