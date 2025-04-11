/*
 * cli_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "app.h"
#include "cli_led.h"
#include "pex.h"
#include "cli_pex.h"
#include "cli_adc.h"
#include "cli_eeprom.h"

exec_t cli_cmd_get(app_t * const app, const char *name) {
	if (!app || !name) {
		return NULL;
	}

	for (uint8_t i = 0; i < app->sc_arr.length; ++i) {
		if (!strcmp(app->sc_arr.cmds[i].name, name)) {
			return app->sc_arr.cmds[i].exec;
		}
	}

	return NULL;
}

uint8_t cli_cmd_add(app_t * const app, const char *name, exec_t exec) {
	if (!app || !name || !exec) {
		return EINVAL;
	}

	if (app->sc_arr.length == APP_MAX_CMDS || strlen(name) > TOKEN_MAX_LENGTH) {
		return EINVAL;
	}

	strcpy(app->sc_arr.cmds[app->sc_arr.length].name, name);

	app->sc_arr.cmds[app->sc_arr.length].exec = exec;

	app->sc_arr.length += 1;

	return 0;
}

__attribute__((weak)) void cli_config(app_t * const app)
{
	cli_cmd_add(app, "dac",  	&cli_dac);
	cli_cmd_add(app, "pex",  	&cli_pex);
	cli_cmd_add(app, "adc",  	&cli_adc);
	cli_cmd_add(app, "eeprom",  &cli_eeprom);
	cli_cmd_add(app, "help",	&cli_help);
	cli_cmd_add(app, "led", 	&cli_led);
}
