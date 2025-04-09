/*
 * config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: artyom
 */

#include "app.h"
#include "led.h"
#include "dac.h"
#include "pex.h"
#include "adc.h"
#include "eeprom.h"

__attribute__((weak)) void app_config(app_t * const app)
{
	app_cmd_add(app, "led", 	&exec_led);
	app_cmd_add(app, "dac",  	&cli_dac);
	app_cmd_add(app, "help",	&exec_help);
	app_cmd_add(app, "pex",  	&exec_pex);
	app_cmd_add(app, "adc",  	&exec_adc);
	app_cmd_add(app, "eeprom",  &exec_eeprom);
}
