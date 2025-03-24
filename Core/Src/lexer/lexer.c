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

	char tokens[TOKEN_MAX_COUNT][TOKEN_MAX_LENGTH];
	memset(tokens, 0, TOKEN_MAX_COUNT * TOKEN_MAX_LENGTH);

	const uint8_t s = tokenize(tokens, input);

	if (s) {
		return s;
	}

	strcpy(cmd->name, tokens[0]);

	for (uint8_t i = 1; tokens[i][0] != '\0'; ++i) {
		strcpy(cmd->args[i - 1], tokens[i]);
	}

	return 0;
}


uint8_t tokenize(char tokens[TOKEN_MAX_COUNT][TOKEN_MAX_LENGTH], char *input) {
	if (!tokens || !input) {
		return EINVAL;
	}

	char *t = NULL;
	uint8_t i = 0;
	// tokenizing the user input
	while((t = strtok(input, WHITESPACE)) != NULL && i < TOKEN_MAX_COUNT) {
		strcpy(tokens[i++], t);
	}

	if (i >= TOKEN_MAX_COUNT - 1) {
		return E2BIG;
	}

	return 0;
}
