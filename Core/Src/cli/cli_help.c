/*
 * cli_help.c
 *
 *  Created on: Apr 11, 2025
 *      Author: Tigran
 */

#include "cli.h"
#include <stdbool.h>
#include <string.h>

struct mruct{
		const char *help;
		const char *option;
};

static struct {
	const char *cmd;
	struct mruct options[HELP_MAX_COUNT];


} cli_help_table[CMD_MAX_COUNT];
static uint16_t size;


const char *cli_get_help(const char *cmd, const char *option)
{
	for (uint16_t i = 0; i < size; ++i) {
		if (!strcmp(cmd, cli_help_table[i].cmd)) {
			for (uint8_t j = 0; cli_help_table[i].options[j].option != NULL; ++j) {
				if (!strcmp(option, cli_help_table[i].options[j].option)) {
					return cli_help_table[i].options[j].help;
				}
			}

			break ;
		}
	}

	return NULL;
}

void cli_set_help(const char *cmd, const char *option, const char *help)
{
	bool increment = true;

	if (size >= CMD_MAX_COUNT){
		return ;
	}

	uint16_t i = 0;
	for (; i < size; ++i) {
		if (!strcmp(cmd, cli_help_table[i].cmd)) {
			increment = false;
			break ;
		}
	}

	cli_help_table[i].cmd = cmd;

	uint8_t j = 0;

	for (; cli_help_table[i].options[j].option != NULL; ++j) {
	}

	if (j >= HELP_MAX_COUNT) {
		return ;
	}

	cli_help_table[i].options[j].help = help;
	cli_help_table[i].options[j].option = option;

	size += increment;
}
