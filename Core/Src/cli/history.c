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

static int32_t history_find(history_t * const history, const char *s) {
	for (int32_t i = HISTORY_SIZE - 1; i > -1 && history->buffer[i][0]; --i) {
		if (strcmp(history->buffer[i], s) == 0) {
			return i;
		}
	}
	return -1;
}

void history_init(history_t * const history) {
	memset(history->buffer, 0, HISTORY_SIZE * FILO_BUFFER_SIZE);
	history->pos = 0;
	history->pivot = history->pos;
	history->shifted = false;
}

void history_set(history_t * const history, const char *s) {

	const int32_t j = history_find(history, s);

	if (j == history->pivot) {
		return;
	}

	if (-1 == j) {
		decrement_pos(history);
		strncpy(history->buffer[history->pos], s, FILO_BUFFER_SIZE);
		return;
	}

	int32_t i = j - 1;
	while (i > -1 && history->buffer[i][0]) {
		strcpy(history->buffer[i + 1], history->buffer[i]);
		--i;
	}

	++i;

	strncpy(history->buffer[i], s, FILO_BUFFER_SIZE);

}

bool history_can_shift(history_t * const history) {
	return (next(history) != history->pivot) && ((!history->shifted && history->buffer[history->pos][0]) != '\0' || (history->shifted && history->buffer[next(history)][0]) != '\0');
}

char *history_shift(history_t *const history) {

	if (history->buffer[history->pos][0] == '\0') {
		return NULL;
	}

	if (history->shifted) {
		increment_pos(history);
	} else {
		history->shifted = true;
	}

	char *res = history->buffer[history->pos];

	return res;
}

char *history_unshift(history_t * const history) {
	if (!history->shifted || history->buffer[history->pos][0] == '\0') {
		return NULL;
	}

	if (history->pos == history->pivot) {
		history->shifted = false;
		return NULL;
	}

	decrement_pos(history);

	char *res = history->buffer[history->pos];

	return res;
}

void history_set_pivot(history_t * const history) {
	history->pivot = history->pos;
	history->shifted = false;
}


void history_reset_pos(history_t * const history) {
	history->pos = history->pivot;
	history->shifted = false;
}

