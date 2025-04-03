/*
 * history.c
 *
 *  Created on: Apr 2, 2025
 *      Author: artyom
 */

#include "cli.h"
#include "../filo/filo.h"
#include "typedefs.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void decrement_pos(history_t *const history) {
	history->pos = (history->pos == 0) ? HISTORY_SIZE - 1 : history->pos - 1;
}

static void increment_pos(history_t *const history) {
	history->pos = (history->pos == HISTORY_SIZE - 1) ? 0 : history->pos + 1;
}

static uint16_t next(history_t * const history) {
	increment_pos(history);
	const uint16_t res = history->pos;
	decrement_pos(history);
	return res;
}

//static uint16_t prev(history_t * const history) {
//	decrement_pos(history);
//	const uint16_t res = history->pos;
//	increment_pos(history);
//	return res;
//}


void history_init(history_t * const history) {
	memset(history->buffer, 0, HISTORY_SIZE * FILO_BUFFER_SIZE);
	history->pos = 0;
	history->pivot = history->pos;
	history->pivot_passed_shift = false;
	history->pivot_passed_unshift = false;
}

void history_set(history_t * const history, const char *str) {
	decrement_pos(history);
	strncpy(history->buffer[history->pos % HISTORY_SIZE], str, FILO_BUFFER_SIZE);
}

char *history_shift(history_t *const history) {
	if (history->buffer[history->pos][0] == '\0') {
		return NULL;
	}

	if (history->pos == history->pivot && history->pivot_passed_shift) {
		history->pivot_passed_unshift = false;
		decrement_pos(history);
		return NULL;
	}

	if (history->pos == history->pivot && !history->pivot_passed_shift) {
		history->pivot_passed_shift = true;
	}

	char *res = history->buffer[history->pos];
	increment_pos(history);
	return res;
}

char *history_unshift(history_t * const history) {
	if (history->buffer[history->pos][0] == '\0') {
		return NULL;
	}

	if (next(history) == history->pivot && history->pivot_passed_unshift) {
		history->pivot_passed_shift = false;
		increment_pos(history);
		return NULL;
	}

	if (history->pos == history->pivot && !history->pivot_passed_unshift) {
		history->pivot_passed_unshift = true;
	}

	char * res = history->buffer[history->pos];
	decrement_pos(history);
	return res;
}

void history_roll(history_t * const history) {
	history->pivot = history->pos;
	history->pivot_passed_shift = false;
	history->pivot_passed_unshift = false;
}
