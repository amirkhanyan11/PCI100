/*
 * lexer.h
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#ifndef SRC_LEXER_LEXER_H_
#define SRC_LEXER_LEXER_H_
#define WHITESPACE " \t\v\n\f\r"

#define ARG_MAX_COUNT 16
#define TOKEN_MAX_LENGTH 32

#include "typedefs.h"

uint8_t tokenize(char tokens[ARG_MAX_COUNT][TOKEN_MAX_LENGTH], char *input);
uint8_t parse(cmd_t * const cmd, char *input);

#endif /* SRC_LEXER_LEXER_H_ */
