/*
 * fifo.c
 *
 *  Created on: Apr 1, 2025
 *      Author: artyom
 */

#include "fifo.h"
#include "typedefs.h"

void fifo_init(fifo_t *fifo) {
	fifo->pos = 0;
	fifo->end = 0;
}

uint8_t fifo_is_empty(fifo_t *fifo) {
	return (fifo->pos >= fifo->end);
}

char fifo_get(fifo_t *fifo) {
	if (fifo_is_empty(fifo)) {
		return -1;
	}
	const char c = fifo->buffer[fifo->pos % FIFO_BUFFER_SIZE];
	fifo->pos += 1;
	return c;
}

void fifo_set(fifo_t *fifo, const char c) {
	fifo->buffer[fifo->end % FIFO_BUFFER_SIZE] = c;
	fifo->end += 1;
}
