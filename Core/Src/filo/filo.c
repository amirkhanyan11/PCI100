/*
 * filo.c
 *
 *  Created on: Apr 1, 2025
 *      Author: artyom
 */


/*
 * fifo.c
 *
 *  Created on: Apr 1, 2025
 *      Author: artyom
 */

#include "filo.h"
#include "typedefs.h"

void filo_init(filo_t *filo) {
	filo->end = 0;
}

void filo_clear(filo_t *filo) {
	filo_init(filo);
}

uint8_t filo_is_empty(filo_t *filo) {
	return (filo->end == 0);
}

char filo_get(filo_t *filo) {
	if (filo_is_empty(filo)) {
		return -1;
	}
	const char c = filo->buffer[(filo->end - 1) % FILO_BUFFER_SIZE];
	filo->end -= 1;
	return c;
}

void filo_set(filo_t *filo, const char c) {
	filo->buffer[filo->end % FILO_BUFFER_SIZE] = c;
	filo->end += 1;
}
