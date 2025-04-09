/*
 * config.c
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

__attribute__((weak)) void app_config(app_t * const app)
{
	app_cmd_add(app, "dac",  	&cli_dac);
	app_cmd_add(app, "pex",  	&cli_pex);
	app_cmd_add(app, "adc",  	&cli_adc);
	app_cmd_add(app, "eeprom",  &cli_eeprom);
	app_cmd_add(app, "help",	&exec_help);
	app_cmd_add(app, "led", 	&cli_led);
}
