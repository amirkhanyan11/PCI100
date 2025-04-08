/*
 * app.c
 *
 *  Created on: Mar 24, 2025
 *      Author: artyom
 */

#include "app.h"
#include "string.h"
#include <errno.h>
#include "cmd.h"
#include "led.h"
#include "dac.h"
#include "led.h"
#include "pex.h"
#include "fifo.h"
#include "adc.h"
#include "eeprom.h"
#include "cli_string_literals.h"

static fifo_t UART_FIFO;

app_t app;

void app_run(app_t * const app) {
	blink_led(&app->led);
	cli_poll(&app->engine);
}

uint8_t app_exec(app_t * const app, char *line) {
	strtrim(line, WHITESPACE);

	const uint16_t line_length = strlen(line);
	if (line_length == 0) {
		return APP_COMMAND_NOT_FOUND;
	} else if (line_length >= FILO_BUFFER_SIZE) {
		printf("error: line too long\r\n");
		return APP_LINE_TOO_LONG;
	}

	cmd_t cmd;
	const uint8_t status = make_cmd(&cmd, app, line);
	if (ESRCH == status) {
		printf("error: command not found\r\n");
		return APP_COMMAND_NOT_FOUND;
	} else if (E2BIG == status) {
		printf("error: token too large\r\n");
		return APP_LINE_TOO_LONG;
	}

	return cmd.exec(&cmd);
}

uint8_t app_init(
		app_t * const app,
		DAC_HandleTypeDef * const hdacx,
		ADC_HandleTypeDef * const hadcx,
		UART_HandleTypeDef * const huartx,
		I2C_HandleTypeDef * const hi2cx,
		SPI_HandleTypeDef * const hspix
) {
	HAL_DAC_Start(hdacx, DAC_CHANNEL_2);
	fifo_init(&UART_FIFO);
	engine_init(&app->engine, &UART_FIFO);

	app->sc_arr.length = 0;

	app->engine.app = app;

	app->hdacx = hdacx;
	app->hadcx = hadcx;
	app->hi2cx = hi2cx;
	app->huartx = huartx;
	app->hspix = hspix;

	led_init(&app->led);

	app_cmd_add(app, "led",  &exec_led);
	app_cmd_add(app, "dac",  &exec_dac);
	app_cmd_add(app, "help", &exec_help);
	app_cmd_add(app, "pex",  &exec_pex);
	app_cmd_add(app, "adc",  &exec_adc);
	app_cmd_add(app, "eeprom",  &exec_eeprom);

	printf("\r\n%s", PROMPT);
	fflush(stdout);

//	HAL_UART_Receive_DMA(app->huartx, app->rx_buf, RX_BUFFER_SIZE);

	// for i2c
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

	return 0;
}

uint8_t app_cmd_add(app_t * const app, const char *name, exec_t exec) {
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


exec_t app_cmd_get(app_t * const app, const char *name) {
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
