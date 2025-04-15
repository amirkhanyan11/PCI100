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
#include <stdarg.h>

exec_t cli_cmd_get_exec(app_t * const app, const char *name)
{
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

uint8_t cli_cmd_add(app_t * const app, const char *name, exec_t exec)
{
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

	cli_cmd_add(app, "led",	&cli_led);
	cli_set_help("led", "on", CLI_LED_ON_OFF_HELP);
	cli_set_help("led", "off", CLI_LED_ON_OFF_HELP);
	cli_set_help("led", "get", CLI_LED_GET_HELP);
	cli_set_help("led", "reset", CLI_LED_RESET_HELP);
	cli_set_help("led", "blink", CLI_LED_BLINK_HELP);


	cli_cmd_add(app, "eeprom",  &cli_eeprom);
	cli_set_help("eeprom", "write", CLI_EEPROM_WRITE_HELP);
	cli_set_help("eeprom", "read", CLI_EEPROM_READ_HELP);
	cli_set_help("eeprom", "read_bulk", CLI_EEPROM_READ_BULK_HELP);

	cli_cmd_add(app, "pex",  	&cli_pex);
	cli_set_help("pex", "write", CLI_PEX_WRITE_HELP);
	cli_set_help("pex", "read", CLI_PEX_READ_HELP);

	cli_cmd_add(app, "dac",  	&cli_dac);
	cli_set_help("dac", "write", CLI_DAC_WRITE_HELP);

	cli_cmd_add(app, "adc",  	&cli_adc);
	cli_set_help("adc", "read", CLI_ADC_READ_HELP);
	cli_cmd_add(app, "help",	&cli_help);
}
