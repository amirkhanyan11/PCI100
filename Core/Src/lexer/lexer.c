/*
 * lexer.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */


#include "lexer.h"
#include <errno.h>
#include <string.h>
#include "../cmd/cmd.h"


uint8_t parse(cmd_t * const cmd, char *input) {
	if (!cmd || !input) {
		return EINVAL;
	}

	char tokens[ARG_MAX_COUNT][TOKEN_MAX_LENGTH];
	memset(tokens, 0, ARG_MAX_COUNT * TOKEN_MAX_LENGTH);

	const uint8_t s = tokenize(tokens, input);

	if (s) {
		return s;
	}

	strcpy(cmd->name, tokens[0]);

	uint8_t i = 1;
	while (tokens[i][0] != '\0') {
		strcpy(cmd->argv[i - 1], tokens[i]);
		++i;
	}

	cmd->argc = i - 1;

	return 0;
}


uint8_t tokenize(char tokens[ARG_MAX_COUNT][TOKEN_MAX_LENGTH], char *input) {
	if (!tokens || !input) {
		return EINVAL;
	}

	char *t = NULL;
	uint8_t i = 0;
	t = strtok(input, WHITESPACE);
	if (strlen(t) >= TOKEN_MAX_LENGTH) {
		return E2BIG;
	}
	if (t) {
		strcpy(tokens[i++], t);
	}
	// tokenizing the user input
	while((t = strtok(NULL, WHITESPACE)) != NULL && i < ARG_MAX_COUNT) {
		if (strlen(t) >= TOKEN_MAX_LENGTH) {
			return E2BIG;
		}
		strcpy(tokens[i++], t);
	}

	if (i >= ARG_MAX_COUNT - 1) {
		return E2BIG;
	}

	return 0;
}
